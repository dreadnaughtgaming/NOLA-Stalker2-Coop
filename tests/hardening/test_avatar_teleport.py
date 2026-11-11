"""Exercise the production body gate with a mocked world and actor API."""
from pathlib import Path
import os
import subprocess
import tempfile
import sys

root = Path(__file__).resolve().parents[2]
source = (root/'src/s2m_bodies.cpp').read_text()
if len(sys.argv) > 1:
    source = Path(sys.argv[1]).read_text()
gate = source[source.index('    bool body_gate()'):source.index('    Ref pup_find(')]
# Only compile the body_gate function, excluding helpers following its closing brace.
start = gate.index('{')
depth = 1
end = start + 1
# This section contains no braces in string literals.
while depth:
    depth += (gate[end] == '{') - (gate[end] == '}')
    end += 1
gate = gate[:end]
helper = ''
far_prefix = ''
if '    void hide_near_bodies(' in source:
    helper = source[source.index('    void hide_near_bodies('):source.index('    void drop_body(')]
    at = source.index('    void far_tick(')
    far_prefix = source[at:source.index('\n        if (!g.hasFarLook)\n', at)] + '\n}\n' 
shim = r'''
#include <algorithm>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cassert>
#include <iostream>
struct Ref { int id=0; uint64_t address() const { return id; } void reset() { id=0; } };
struct Vec3 { double x=0,y=0,z=0; };
struct Body { Ref pawn; bool hidden=false; std::optional<double> spawnAt; };
struct Far { Ref actor; std::optional<bool> hidden; };
struct Pl { Body pup,tgt; Far far; };
namespace lg {
    struct RSnap {};
    struct Hold { bool held=false; };
    std::string inum(int64_t v) { return std::to_string(v); }
    void hold_arm(Hold& h,bool on,double) { h.held=on; }
    std::string hold_step(Hold& h,bool,bool stable,int,double,double) { if(stable) h.held=false; return {}; }
}
struct Gate {
    std::optional<std::string> key;
    std::optional<double> since;
    std::optional<std::pair<double,double>> lp;
    bool open=false;
    lg::Hold hold;
};
struct St { Pl pl[4]; Gate wg; bool hasFarLook=false; } state;
St& S() { return state; }
double clock_now=20;
Ref local{1}; Vec3 position{20000,0,0};
std::vector<int> hidden;
int drops=0;
bool hide_ok=true;
namespace x0 { using Ref=::Ref; double now(){return clock_now;} std::string full_name(Ref r){return "pawn"+std::to_string(r.id);} }
Ref local_pawn(){ return local; }
bool valid(Ref r){return r.id>0;}
bool has(Ref r){return valid(r);}
bool body_ok(const Body& b){return valid(b.pawn);}
bool loc(Ref,Vec3& p){p=position;return true;}
double FL(const char* key,double fallback){return std::string(key)=="qhold"?0:fallback;}
void drop_body(Body& b){++drops;b.pawn.reset();b.spawnAt.reset();}
bool hide_actor(Ref r,bool hide){assert(hide&&r.id!=local.id);hidden.push_back(r.id);return hide_ok;}
void far_hide(Far& f){hide_actor(f.actor,true);f.hidden=true;}
void LOG(const std::string&){}
std::string tf(bool b){return b?"true":"false";}
std::string fmt(const char* text,...){char b[512];va_list a;va_start(a,text);vsnprintf(b,sizeof b,text,a);va_end(a);return b;}
int quests_pending(){return 0;}
Pl& V(){return state.pl[0];}
bool far_capture(Ref){state.hasFarLook=true;return true;}
'''
# Gate.lp is the optional local position in the actual implementation.
main = r'''
void setup() {
    state=St{}; hidden.clear(); drops=0; hide_ok=true; local={1}; clock_now=20; position={20000,0,0};
    state.wg.key="1|pawn1"; state.wg.since=0; state.wg.lp=std::make_pair(0.0,0.0); state.wg.open=true;
    for(int v=0;v<2;++v) { state.pl[v].pup.pawn={10+v*10}; state.pl[v].tgt.pawn={11+v*10}; state.pl[v].far.actor={12+v*10}; }
    state.pl[2].pup.spawnAt=77;
}
int main() {
    setup(); assert(!body_gate());
    assert(drops==0 && "teleport must retain player bodies");
    for(int v=0;v<2;++v) { assert(state.pl[v].pup.pawn.id==10+v*10); assert(state.pl[v].tgt.pawn.id==11+v*10); assert(state.pl[v].far.actor.id==12+v*10); assert(state.pl[v].pup.hidden); }
    assert(hidden.size()==6 && state.pl[2].pup.spawnAt==77);
    clock_now=26; assert(body_gate()); assert(drops==0);
    position.x+=20000; assert(!body_gate()); assert(drops==0&&hidden.size()==12);
    clock_now=32; assert(body_gate());
    setup(); position={100,0,0}; assert(body_gate()); assert(hidden.empty()&&drops==0);
    setup(); hide_ok=false; assert(!body_gate()); assert(drops==0&&state.pl[0].pup.pawn.id==10&&!state.pl[0].pup.hidden);
    setup(); local={2}; assert(!body_gate()); assert(drops==8&&hidden.empty());
    for(const auto& p:state.pl) assert(!p.pup.pawn.id&&!p.tgt.pawn.id&&!p.far.actor.id);
    setup(); far_tick(state.pl[0].far,lg::RSnap{},position,clock_now);
    assert(state.hasFarLook && state.pl[0].pup.pawn.id==10 && state.pl[0].tgt.pawn.id==11 && state.pl[0].pup.hidden);
    assert(state.pl[2].pup.spawnAt==77 && drops==0);
    std::cout << "Avatar teleport and far-body retention regression PASS\n";
}
'''
with tempfile.TemporaryDirectory() as folder:
    out=Path(folder)
    (out/'test.cpp').write_text(shim+helper+far_prefix+gate+(main if far_prefix else main[:main.index('    setup(); far_tick')]+'}'))
    subprocess.run(['g++','-std=c++20','-O1','-g','-fsanitize=address,undefined',str(out/'test.cpp'),'-o',str(out/'test')],check=True)
    subprocess.run([str(out/'test')],check=True,env={**os.environ,'ASAN_OPTIONS':'detect_leaks=0'})
