#include "s2m_money_core.h"
#include <cassert>
#include <iostream>
using namespace s2m::money;
struct Wallet
{
    int64_t money = 1000;
    int changes = 0;
    bool journal_ok = true, change_ok = true, partial_change = false;
    std::string journal;
    Backend backend()
    {
        return {[this](int64_t& n) { n = money; return true; },
            [this](int64_t d) { ++changes; if (change_ok || partial_change) money += d; return change_ok; },
            [this](const std::string& s) { if (!journal_ok) return false; journal += s + "\n"; return true; }};
    }
};
const std::string alice(32, 'a'), bob(32, 'b'), carol(32, 'c');
int main()
{
    {
        Wallet a,b; Ledger sender(alice,a.backend()), receiver(bob,b.backend());
        assert(sender.send(bob,250)); assert(a.money==750);
        auto request=sender.outgoing(); auto ack=receiver.receive(request,alice,true);
        assert(b.money==1250); assert(receiver.receive(request,alice,true)==ack); assert(b.changes==1);
        sender.acknowledge(ack,carol); assert(sender.busy());
        sender.acknowledge(ack,bob); sender.acknowledge(ack,bob);
        assert(!sender.busy()&&a.changes==1&&a.money+b.money==2000);
        Ledger restarted(std::string(32,'d'),b.backend()); assert(restarted.restore(b.journal));
        assert(restarted.receive(request,alice,true).empty()); assert(b.changes==1);
        assert(sender.send(bob,50)); auto next=sender.outgoing();
        sender.acknowledge(ack,bob); assert(sender.busy());
        sender.acknowledge(receiver.receive(next,alice,true),bob); assert(!sender.busy());
    }
    {
        Wallet a,b; Ledger sender(alice,a.backend()), receiver(bob,b.backend());
        assert(!sender.send(bob,1001)); assert(!sender.send(bob,0)); assert(!sender.send(bob,-1));
        assert(!sender.send(alice,1)); assert(a.changes==0);
        assert(sender.send(bob,100)); auto ack=receiver.receive(sender.outgoing(),alice,false);
        sender.acknowledge(ack,bob); sender.acknowledge(ack,bob);
        assert(a.money==1000&&b.money==1000&&a.changes==2&&b.changes==0);
    }
    {
        Wallet a,b; Ledger sender(alice,a.backend()), receiver(bob,b.backend());
        a.journal_ok=false; assert(!sender.send(bob,100)); assert(a.changes==0&&sender.busy());
    }
    {
        Wallet a,b; Ledger sender(alice,a.backend()), receiver(bob,b.backend());
        assert(sender.send(bob,100)); b.journal_ok=false;
        sender.acknowledge(receiver.receive(sender.outgoing(),alice,true),bob);
        assert(sender.unresolved()&&a.money==900&&b.changes==0);
    }
    {
        Wallet a,b; Ledger sender(alice,a.backend()), receiver(bob,b.backend());
        assert(sender.send(bob,100)); b.change_ok=false;
        auto request=sender.outgoing(); auto ack=receiver.receive(request,alice,true);
        assert(receiver.unresolved()); assert(receiver.receive(request,alice,true)==ack&&b.changes==1);
        sender.acknowledge(ack,bob); assert(sender.unresolved()&&a.money==900);
        Ledger restarted(std::string(32,'d'),a.backend()); assert(restarted.restore(a.journal)); assert(restarted.busy());
    }
    {
        Wallet a; a.change_ok=false; a.partial_change=true; Ledger sender(alice,a.backend());
        assert(sender.send(bob,100)); assert(a.changes==1&&a.money==900);
        sender.interrupt(); assert(sender.outgoing().empty()); assert(!sender.send(bob,100));
    }
    {
        Wallet a; Ledger sender(alice,a.backend()); assert(!sender.restore("truncated")); assert(sender.busy());
        Transfer t; char state; assert(!parse("1 S "+alice+" "+bob+" 1 100 garbage",t,state));
        assert(!parse("1 S "+alice+" "+bob+" 1 9999999999999999999999999",t,state));
    }
    {
        Wallet a,b; Ledger sender(alice,a.backend()), receiver(bob,b.backend());
        assert(sender.send(bob,100)); auto request=sender.outgoing();
        Transfer t; char state; assert(parse(request,t,state));
        assert(receiver.receive(request,carol,true).empty());
        auto ack=receiver.receive(request,alice,true); ++t.amount;
        assert(receiver.receive(wire(t,'S'),alice,true).empty());
        sender.acknowledge(wire(t,'A'),bob); assert(sender.busy());
        sender.acknowledge(ack,bob); assert(!sender.busy());
        assert(a.money+b.money==2000);
    }
    {
        Wallet a; Ledger sender(alice,a.backend());
        Transfer t{bob,alice,1,50};
        assert(sender.restore(wire(t,'I')+"\n")); assert(sender.unresolved());
        auto ack=sender.receive(wire(t,'S'),bob,true);
        char state=0; assert(parse(ack,t,state)&&state=='U');
        assert(a.changes==0);
    }
    {
        Wallet a,b; b.money=max_balance; Ledger sender(alice,a.backend()), receiver(bob,b.backend());
        assert(sender.send(bob,1)); auto ack=receiver.receive(sender.outgoing(),alice,true);
        sender.acknowledge(ack,bob); assert(a.money==1000&&b.money==max_balance);
    }
    {
        Wallet a; auto backend=a.backend(); backend.change=[](int64_t)->bool { throw 42; };
        Ledger sender(alice,backend); assert(!sender.send(bob,1));
        assert(sender.unresolved()&&sender.outgoing().empty());
    }
    {
        Wallet a; auto backend=a.backend(); backend.record=[](const std::string&)->bool { throw 42; };
        Ledger sender(alice,backend); assert(!sender.send(bob,1)); assert(a.changes==0);
    }
    {
        Wallet b; auto backend=b.backend(); int writes=0;
        backend.record=[&](const std::string& line) { ++writes; if(writes==2) return false; b.journal+=line+"\n"; return true; };
        Ledger receiver(bob,backend); Transfer t{alice,bob,1,100};
        auto ack=receiver.receive(wire(t,'S'),alice,true); assert(b.money==1100&&b.changes==1);
        assert(receiver.receive(wire(t,'S'),alice,true)==ack&&b.changes==1);
        Ledger restart(bob,b.backend()); assert(restart.restore(b.journal)&&restart.unresolved());
        restart.receive(wire(t,'S'),alice,true); assert(b.changes==1);
    }
    std::cout << "Money transfer regression tests passed\n";
}
