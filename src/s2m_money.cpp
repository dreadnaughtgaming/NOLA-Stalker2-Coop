#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include "s2m_money.h"
#include "s2m_money_core.h"
#include "s2m_bodies.h"
#include "s2m_damage.h"
#include "s2m_save.h"
#include <cmath>
#include <memory>
#include <random>
#include <array>

namespace s2m::money
{
    namespace
    {
        using x0::Ref;
        std::unique_ptr<Ledger> ledger;
        std::string nonce, shown;
        Ref pawn, owner, bound_world;
        HWND panel = nullptr, amount_edit = nullptr, status_text = nullptr;
        int target_view = -1, pending_view = -1;
        std::string target_nonce, target_peer, pending_peer;
        int target_session = 0, pending_session = 0;
        double sent_at = 0;
        bool send_clicked = false;
        bool debit_allowed = false;
        std::map<int, std::string> replies;
        std::array<std::string, 5> reply_peer;
        std::array<int, 5> reply_session{};

        Ref controller()
        {
            for (const Ref& r : x0::all_of(L"PlayerController"))
                if (x0::call_b(r, L"IsLocalPlayerController", false)) return r;
            return {};
        }
        Ref local_pawn()
        {
            Ref p, pc = controller();
            return pc && x0::prop<Ref>(pc, "Pawn", p) && p ? p : Ref{};
        }
        bool ready()
        {
            return x0::coop() && pawn && !s2m::damage::local_downed() && x0::call_b(pawn, L"IsAlive", false) &&
                !m01::world_held() && !m01::quest_graph_held() && !(m01::ext().remote_cine && m01::ext().remote_cine()) &&
                !s2m_save::joinBusy() && !s2m_save::joinPending() && !s2m_save::leaveWait();
        }
        bool wallet(int64_t& value)
        {
            if (!pawn) return false;
            x0::Call call(pawn, L"GetMoney");
            if (!call.run()) return false;
            double v = call.rf();
            if (!std::isfinite(v) || v < 0 || v > max_balance || std::floor(v) != v) return false;
            value = static_cast<int64_t>(v);
            return true;
        }
        bool change(int64_t delta)
        {
            if (!pawn || !debit_allowed) return false;
            x0::Call call(pawn, L"ModifyMoney");
            return call.i(L"Delta", delta).run();
        }
        bool record(const std::string& entry)
        {
            HANDLE file = CreateFileW(x0::bridge_file(L"money-transactions.log").c_str(), FILE_APPEND_DATA, FILE_SHARE_READ,
                nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
            if (file == INVALID_HANDLE_VALUE) return false;
            LARGE_INTEGER size{};
            std::string data = entry + "\n";
            DWORD written = 0;
            bool ok = GetFileSizeEx(file, &size) && size.QuadPart < 2 * 1024 * 1024 &&
                WriteFile(file, data.data(), static_cast<DWORD>(data.size()), &written, nullptr) && written == data.size() && FlushFileBuffers(file);
            CloseHandle(file);
            return ok;
        }
        bool fresh(int view)
        {
            if (view < 0 || view >= x0::views()) return false;
            const auto& s = x0::remote(view);
            return x0::peer(view).live && s.ok && s.has_pos && s.recv >= 0 && x0::now() - s.recv >= 0 && x0::now() - s.recv < 2;
        }
        std::string capability(int view)
        {
            std::string data;
            if (!fresh(view) || !x0::rpart("XC", data, view)) return {};
            return data.rfind("1 ", 0) == 0 && nonce_ok(data.substr(2)) ? data.substr(2) : std::string();
        }
        int aimed_player()
        {
            Ref pc = controller(), cam;
            x0::Vec3 origin;
            x0::Rot rotation;
            if (!pc || !x0::prop<Ref>(pc, "PlayerCameraManager", cam) || !cam) return -1;
            x0::Call pos(cam, L"GetCameraLocation"), rot(cam, L"GetCameraRotation");
            if (!pos.run() || !pos.rv(origin) || !rot.run() || !rot.rr(rotation)) return -1;
            const double radians = 3.14159265358979323846 / 180;
            x0::Vec3 direction{std::cos(rotation.pitch * radians) * std::cos(rotation.yaw * radians),
                std::cos(rotation.pitch * radians) * std::sin(rotation.yaw * radians), std::sin(rotation.pitch * radians)};
            int best = -1;
            double nearest = 500;
            x0::each_view([&](int view, const x0::Snap& s, const x0::Peer&) {
                if ((!x0::is_host() && x0::view_pid(view) != 0) || capability(view).empty() || s2m::damage::remote_down(view)) return;
                x0::Vec3 target{s.x, s.y, s.z + 65};
                double dx = target.x - origin.x, dy = target.y - origin.y, dz = target.z - origin.z;
                double along = dx * direction.x + dy * direction.y + dz * direction.z;
                double perpendicular = dx * dx + dy * dy + dz * dz - along * along;
                if (along <= 0 || along >= nearest || perpendicular > 65 * 65) return;
                bool hit = false; x0::Vec3 impact;
                if (!x0::trace_line(origin, target, hit, impact)) return;
                double ix = impact.x - origin.x, iy = impact.y - origin.y, iz = impact.z - origin.z;
                if (hit && ix * ix + iy * iy + iz * iz < (along - 85) * (along - 85)) return;
                best = view; nearest = along;
            });
            return best;
        }
        void close_panel()
        {
            if (panel) DestroyWindow(panel);
            panel = amount_edit = status_text = nullptr;
            target_view = -1;
            send_clicked = false;
        }
        LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
        {
            if (message == WM_COMMAND && LOWORD(wparam) == 1)
            {
                send_clicked = true;
                // Return focus so games configured to pause in the background can process the request.
                ShowWindow(window, SW_HIDE);
                SetForegroundWindow(GetWindow(window, GW_OWNER));
                return 0;
            }
            if (message == WM_CLOSE) { close_panel(); return 0; }
            return DefWindowProcW(window, message, wparam, lparam);
        }
        void open_panel()
        {
            if (panel) { close_panel(); return; }
            if (!ledger || !ready()) return;
            if (ledger->busy()) { x0::ui_msg("money", ledger->message, 8); return; }
            int view = aimed_player();
            if (view < 0) { x0::ui_msg("money", "Look at a nearby standing teammate with money-transfer support, then press INSERT.", 6); return; }
            target_view = view; target_nonce = capability(view);
            target_peer = x0::peer(view).id; target_session = x0::peer(view).sessions;
            owner = pawn; bound_world = x0::world();
            WNDCLASSW cls{};
            cls.lpfnWndProc = window_proc;
            cls.hInstance = GetModuleHandleW(nullptr);
            cls.lpszClassName = L"NolaMoneyTransfer";
            cls.hCursor = LoadCursorW(nullptr, IDC_ARROW);
            cls.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
            if (!RegisterClassW(&cls) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) return;
            std::wstring player = x0::view_pid(view) == 0 ? L"HOST" : L"PLAYER " + std::to_wstring(x0::view_pid(view));
            std::wstring title = L"Send coupons to " + player;
            panel = CreateWindowExW(WS_EX_DLGMODALFRAME, cls.lpszClassName, title.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                CW_USEDEFAULT, CW_USEDEFAULT, 440, 200, GetForegroundWindow(), nullptr, cls.hInstance, nullptr);
            if (!panel) return;
            int64_t balance = 0;
            std::wstring label = wallet(balance) ? L"Your balance: " + std::to_wstring(balance) + L" coupons" : L"Wallet unavailable";
            CreateWindowW(L"STATIC", label.c_str(), WS_CHILD | WS_VISIBLE, 16, 16, 400, 24, panel, nullptr, cls.hInstance, nullptr);
            amount_edit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_AUTOHSCROLL,
                16, 50, 265, 30, panel, nullptr, cls.hInstance, nullptr);
            SendMessageW(amount_edit, EM_SETLIMITTEXT, 7, 0);
            CreateWindowW(L"BUTTON", L"Send", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 295, 50, 110, 30, panel,
                reinterpret_cast<HMENU>(static_cast<INT_PTR>(1)), cls.hInstance, nullptr);
            status_text = CreateWindowW(L"STATIC", L"Enter a whole amount (1 to 1000000).", WS_CHILD | WS_VISIBLE,
                16, 95, 390, 45, panel, nullptr, cls.hInstance, nullptr);
            ShowWindow(panel, SW_SHOW);
            SetForegroundWindow(panel);
            SetFocus(amount_edit);
        }
        void tick()
        {
            pawn = local_pawn();
            if (ledger->busy() && pending_view >= 0 && (!ready() || !owner.same(pawn) || !bound_world.same(x0::world()) ||
                !fresh(pending_view) || x0::peer(pending_view).id != pending_peer || x0::peer(pending_view).sessions != pending_session)) ledger->interrupt();
            if (panel && (!ready() || !owner.same(pawn) || !bound_world.same(x0::world()) || !fresh(target_view) ||
                x0::peer(target_view).id != target_peer || x0::peer(target_view).sessions != target_session || capability(target_view) != target_nonce)) close_panel();
            debit_allowed = ready();
            if (panel && send_clicked)
            {
                send_clicked = false;
                wchar_t text[32]{}; GetWindowTextW(amount_edit, text, 32);
                std::string digits;
                for (wchar_t ch : std::wstring(text)) digits += ch >= L'0' && ch <= L'9' ? static_cast<char>(ch) : '?';
                int64_t amount = 0;
                auto parsed = std::from_chars(digits.data(), digits.data() + digits.size(), amount);
                if (digits.empty() || parsed.ec != std::errc{} || parsed.ptr != digits.data() + digits.size())
                    SetWindowTextW(status_text, L"Enter a whole amount from 1 to 1000000.");
                else
                {
                    pending_view = target_view; pending_peer = target_peer; pending_session = target_session;
                    if (ledger->send(target_nonce, amount)) { sent_at = x0::now(); close_panel(); }
                    else SetWindowTextW(status_text, std::wstring(ledger->message.begin(), ledger->message.end()).c_str());
                }
            }
            if (panel && !IsWindowVisible(panel))
            {
                ShowWindow(panel, SW_SHOW);
                SetForegroundWindow(panel);
            }
            x0::each_view([&](int view, const x0::Snap&, const x0::Peer& peer) {
                if (view < 0 || view >= static_cast<int>(reply_peer.size())) return;
                if (reply_peer[view] != peer.id || reply_session[view] != peer.sessions)
                { replies.erase(view); reply_peer[view] = peer.id; reply_session[view] = peer.sessions; }
                if (!x0::is_host() && x0::view_pid(view) != 0) return;
                std::string cap = capability(view), data;
                if (cap.empty() || !x0::coop()) return;
                if (x0::rpart("XT", data, view))
                {
                    std::string receipt = ledger->receive(data, cap, ready());
                    if (!receipt.empty()) replies[view] = receipt;
                }
                if (view == pending_view && peer.id == pending_peer && peer.sessions == pending_session && x0::rpart("XA", data, view))
                    ledger->acknowledge(data, cap);
            });
            if (!ledger->outgoing().empty() && x0::now() - sent_at > 15) ledger->interrupt();
            if (shown != ledger->message && !ledger->message.empty())
            { shown = ledger->message; x0::ui_msg("money", shown, 8); x0::log("NOLA money: " + shown); }
        }
    }
    void shutdown()
    {
        // The DLL may be destroyed outside the window-owning game thread.
        // Detach callbacks before asking that thread to destroy the native window.
        if (panel)
        {
            SetWindowLongPtrW(panel, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(DefWindowProcW));
            SetClassLongPtrW(panel, GCLP_WNDPROC, reinterpret_cast<LONG_PTR>(DefWindowProcW));
            PostMessageW(panel, WM_CLOSE, 0, 0);
            panel = amount_edit = status_text = nullptr;
        }
        UnregisterClassW(L"NolaMoneyTransfer", GetModuleHandleW(nullptr));
    }
    void init()
    {
        std::random_device random;
        const char* hex = "0123456789abcdef";
        for (int i = 0; i < 32; ++i) nonce += hex[random() & 15];
        ledger = std::make_unique<Ledger>(nonce, Backend{wallet, change, record});
        std::string journal;
        auto path = x0::bridge_file(L"money-transactions.log");
        if (x0::read_text(path, journal)) ledger->restore(journal);
        else if (GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES || GetLastError() != ERROR_FILE_NOT_FOUND) ledger->restore("unreadable journal");
        x0::own_tag(x0::Mod::damage, "XC", [] { return "#XC:1 " + nonce; });
        x0::own_tag(x0::Mod::damage, "XT", [] { auto s = ledger->outgoing(); return s.empty() ? s : "#XT:" + s; });
        x0::own_tag_view(x0::Mod::damage, "XA", [](int view) { auto i = replies.find(view); return i == replies.end() ? std::string() : "#XA:" + i->second; });
        x0::key(x0::Mod::damage, VK_INSERT, open_panel);
        x0::every(x0::Mod::damage, "moneyTransfer", x0::Rate::t100, tick);
    }
}
