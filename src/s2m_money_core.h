#pragma once
#include <charconv>
#include <cstdint>
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <limits>

namespace s2m::money
{
    constexpr int64_t max_amount = 1000000;
    constexpr int64_t max_balance = 16777215;
    struct Transfer
    {
        std::string from, to;
        uint64_t seq = 0;
        int64_t amount = 0;
        std::string key() const { return from + "/" + std::to_string(seq); }
        bool same(const Transfer& b) const { return from == b.from && to == b.to && seq == b.seq && amount == b.amount; }
    };
    inline bool nonce_ok(const std::string& n)
    {
        return n.size() == 32 && n.find_first_not_of("0123456789abcdef") == std::string::npos;
    }
    inline bool parse(const std::string& s, Transfer& t, char& state)
    {
        if (s.size() > 160) return false;
        std::istringstream in(s);
        std::string version, seq, amount, extra;
        if (!(in >> version >> state >> t.from >> t.to >> seq >> amount) || in >> extra || version != "1") return false;
        auto q = std::from_chars(seq.data(), seq.data() + seq.size(), t.seq);
        auto a = std::from_chars(amount.data(), amount.data() + amount.size(), t.amount);
        return q.ec == std::errc{} && q.ptr == seq.data() + seq.size() && t.seq > 0 &&
            a.ec == std::errc{} && a.ptr == amount.data() + amount.size() && t.amount > 0 && t.amount <= max_amount &&
            nonce_ok(t.from) && nonce_ok(t.to) && t.from != t.to;
    }
    inline std::string wire(const Transfer& t, char state)
    {
        return "1 " + std::string(1, state) + " " + t.from + " " + t.to + " " + std::to_string(t.seq) + " " + std::to_string(t.amount);
    }
    struct Backend
    {
        std::function<bool(int64_t&)> balance;
        std::function<bool(int64_t)> change;
        // Must persist and flush before returning success. Never mutate money if this fails.
        std::function<bool(const std::string&)> record;
    };
    class Ledger
    {
        struct Receipt { Transfer transfer; char state = 'U'; };
        Backend io;
        std::map<std::string, Receipt> receipts;
        std::string self;
        uint64_t next = 0;
        Transfer pending;
        bool active = false, funded = false, blocked = false, broken = false;
        bool append(const Transfer& t, char state)
        {
            try { if (!broken && io.record(wire(t, state))) return true; }
            catch (...) {}
            broken = blocked = true; return false;
        }
        bool mutate(int64_t delta)
        {
            try
            {
                int64_t before = 0, after = 0;
                if (!io.balance(before) || before < 0 || before > max_balance || delta < -before || delta > max_balance - before) return false;
                // A failed native call may still have changed the wallet. Never call it twice.
                io.change(delta);
                return io.balance(after) && after == before + delta;
            }
            catch (...) { return false; }
        }
      public:
        std::string message;
        Ledger(std::string nonce, Backend backend) : io(std::move(backend)), self(std::move(nonce)) {}
        bool busy() const { return active || blocked || broken; }
        bool unresolved() const { return blocked || broken; }
        std::string outgoing() const { return active && funded && !blocked && !broken ? wire(pending, 'S') : std::string(); }
        void interrupt()
        {
            if (active) { blocked = true; message = "Transfer unresolved. Further sending is blocked. Keep the money journal for review."; }
        }
        bool restore(const std::string& journal)
        {
            std::istringstream in(journal);
            std::string line;
            std::map<std::string, char> outgoing;
            while (std::getline(in, line))
            {
                if (line.empty()) continue;
                Transfer t; char state = 0;
                if (!parse(line, t, state)) { broken = blocked = true; return false; }
                if (state == 'I' || state == 'A' || state == 'R') receipts[t.key()] = {t, state == 'I' ? 'U' : state};
                else if (state == 'D' || state == 'S' || state == 'F' || state == 'C') outgoing[t.key()] = state;
                else { broken = blocked = true; return false; }
            }
            for (const auto& entry : outgoing) if (entry.second != 'C') blocked = true;
            for (const auto& entry : receipts) if (entry.second.state == 'U') blocked = true;
            if (blocked) message = "Previous transfer unresolved. Keep the money journal for review; sending is blocked.";
            return true;
        }
        bool send(const std::string& recipient, int64_t amount)
        {
            if (busy()) { message = "Another transfer is pending or unresolved."; return false; }
            int64_t balance = 0;
            if (!nonce_ok(self) || !nonce_ok(recipient) || self == recipient || amount <= 0 || amount > max_amount)
            { message = "Enter a whole amount from 1 to 1000000."; return false; }
            if (!io.balance(balance) || balance < amount || balance > max_balance)
            { message = "Insufficient balance or wallet unavailable."; return false; }
            if (next == std::numeric_limits<uint64_t>::max()) return false;
            pending = {self, recipient, ++next, amount};
            if (!append(pending, 'D')) { message = "Cannot save the transaction journal. Sending is blocked."; return false; }
            active = true; funded = false;
            if (!mutate(-amount) || !append(pending, 'S')) { interrupt(); return false; }
            funded = true;
            message = "Money deducted. Waiting for the recipient to confirm...";
            return true;
        }
        std::string receive(const std::string& data, const std::string& expected_sender, bool ready)
        {
            Transfer t; char state = 0;
            if (!parse(data, t, state) || state != 'S' || t.to != self || t.from != expected_sender) return {};
            auto it = receipts.find(t.key());
            if (it != receipts.end()) return it->second.transfer.same(t) ? wire(t, it->second.state) : std::string();
            if (broken) return wire(t, 'U');
            if (receipts.size() >= 4096) return wire(t, 'U');
            int64_t balance = 0;
            if (!ready || !io.balance(balance) || balance < 0 || balance > max_balance - t.amount)
            {
                if (!append(t, 'R')) return wire(t, 'U');
                receipts[t.key()] = {t, 'R'};
                return wire(t, 'R');
            }
            if (!append(t, 'I')) return wire(t, 'U');
            receipts[t.key()] = {t, 'U'};
            if (!mutate(t.amount) || !append(t, 'A'))
            { blocked = true; message = "Incoming transfer unresolved. Keep the money journal for review."; return wire(t, 'U'); }
            receipts[t.key()].state = 'A';
            message = "Received " + std::to_string(t.amount) + " coupons.";
            return wire(t, 'A');
        }
        void acknowledge(const std::string& data, const std::string& expected_recipient)
        {
            Transfer t; char state = 0;
            if (!active || blocked || broken || !parse(data, t, state) || !pending.same(t) || t.to != expected_recipient) return;
            if (state == 'U') { interrupt(); return; }
            if (state == 'A')
            {
                if (!append(t, 'C')) { interrupt(); return; }
                active = false; message = "Sent " + std::to_string(t.amount) + " coupons.";
            }
            else if (state == 'R')
            {
                if (!append(t, 'F') || !mutate(t.amount) || !append(t, 'C')) { interrupt(); return; }
                active = false; message = "Transfer declined. " + std::to_string(t.amount) + " coupons returned.";
            }
        }
    };
}
