#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main () {
    NodeContainer nodes;
    nodes.Create (20);

    InternetStackHelper internet;
    internet.Install (nodes);

    CsmaHelper csma;
    csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
    csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

    csma.Install (nodes);

    AnimationInterface anim ("bus.xml");

    for (uint32_t i = 0; i < 20; i++) {
        anim.SetConstantPosition (nodes.Get (i), 10 + i * 5, 50);
    }

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}
