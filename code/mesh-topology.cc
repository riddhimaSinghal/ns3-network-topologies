#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main () {
    NodeContainer nodes;
    nodes.Create (16);

    InternetStackHelper internet;
    internet.Install (nodes);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
    p2p.SetChannelAttribute ("Delay", StringValue ("1ms"));

    for (uint32_t i = 0; i < 16; i++) {
        for (uint32_t j = i + 1; j < 16; j++) {
            NodeContainer pair (nodes.Get (i), nodes.Get (j));
            p2p.Install (pair);
        }
    }

    AnimationInterface anim ("mesh.xml");

    uint32_t k = 0;
    for (uint32_t x = 0; x < 4; x++) {
        for (uint32_t y = 0; y < 4; y++) {
            anim.SetConstantPosition (nodes.Get (k), 20 + x * 20, 20 + y * 20);
            k++;
        }
    }

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}
