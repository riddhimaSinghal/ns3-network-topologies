#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main () {
    NodeContainer nodes;
    nodes.Create (15);

    InternetStackHelper internet;
    internet.Install (nodes);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
    p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

    for (uint32_t i = 1; i < 15; i++) {
        NodeContainer pair (nodes.Get (0), nodes.Get (i));
        p2p.Install (pair);
    }

    AnimationInterface anim ("star.xml");
    anim.SetConstantPosition (nodes.Get (0), 50, 50);

    for (uint32_t i = 1; i < 15; i++) {
        anim.SetConstantPosition (nodes.Get (i), 20 + i * 4, 80);
    }

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}
