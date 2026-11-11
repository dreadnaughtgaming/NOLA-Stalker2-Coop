"""Run the production bridge reset and NPC host cleanup with mocked engine calls."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory() as folder:
    out = Path(folder)
    tests = (root / 'tests/x0/test_x0.cpp').read_text()
    case = tests[tests.index('static void t_session_reset()'):tests.index('int main(int argc, char** argv)')]
    shim = r'''
#include "s2x_int.h"
#include <cassert>
#include <iostream>
using namespace x0;
using namespace x0::in;
static void check(bool ok, const std::string& message) { if (!ok) { std::cerr << message << "\n"; std::abort(); } }
namespace x0 {
    double now() { return 100; }
    std::vector<std::string> split(std::string_view s, char delimiter, bool keep) {
        std::vector<std::string> result;
        size_t pos = 0;
        while (pos <= s.size()) {
            size_t end = s.find(delimiter, pos);
            if (end == std::string_view::npos) end = s.size();
            if (keep || end > pos) result.emplace_back(s.substr(pos, end - pos));
            if (end == s.size()) break;
            pos = end + 1;
        }
        return result;
    }
}
'''
    (out / 'test.cpp').write_text(shim + case + '\nint main() { t_session_reset(); std::cout << "Session reset PASS\\n"; }\n')
    common = ['g++', '-std=c++20', '-O1', '-g', '-fsanitize=address,undefined', '-ffunction-sections', '-fdata-sections', '-I'+str(root/'src')]
    subprocess.run(common + [str(out/'test.cpp'), str(root/'src/s2x_bridge.cpp'), '-Wl,--gc-sections', '-o', str(out/'test')], check=True)
    subprocess.run([str(out/'test')], check=True)
    native = (root/'src/s2n_nat.cpp').read_text()
    cleanup = native[native.index('    auto host_reset()'):native.index('    auto host_api(')]
    shim = r'''
#include <map>
#include <string>
#include <cassert>
#include <iostream>
struct Ref { bool valid = true; void* get() { return valid ? this : nullptr; } };
struct Selected { Ref r; };
struct HostSt { std::map<int,Selected> sel; std::string cached = ""; int generation = 0; } H;
int restored = 0, detached = 0;
void ag_update(void* p) { assert(!p); ++detached; }
void dmg_update(void* a, void* b) { assert(!a && !b); ++detached; }
void host_offa(Selected&, void*, bool on) { assert(!on); ++restored; }
'''
    main = r'''
int main() {
    H.sel[1] = {}; H.sel[2] = {}; H.cached = "old host NPCs"; H.generation = 7;
    host_reset(); assert(restored == 2 && detached == 2);
    assert(H.sel.empty() && H.cached.empty() && H.generation == 0);
    host_reset(); assert(restored == 2 && detached == 4);
    std::cout << "NPC host cleanup PASS\n";
}
'''
    (out/'host.cpp').write_text(shim+cleanup+main)
    subprocess.run(common+[str(out/'host.cpp'), '-o', str(out/'host')], check=True)
    subprocess.run([str(out/'host')], check=True)
