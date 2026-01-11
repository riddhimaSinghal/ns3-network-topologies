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

    for (uint32_t i = 0; i < 14; i++) {
        NodeContainer pair (nodes.Get (i), nodes.Get (i + 1));
        p2p.Install (pair);
    }

    NodeContainer lastPair (nodes.Get (14), nodes.Get (0));
    p2p.Install (lastPair);

    AnimationInterface anim ("ring.xml");

    double angle;
    for (uint32_t i = 0; i < 15; i++) {
        angle = 2 * M_PI * i / 15;
        anim.SetConstantPosition (nodes.Get (i),
            50 + 30 * cos (angle),
            50 + 30 * sin (angle));
    }

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}
