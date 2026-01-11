#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main () {

    NodeContainer starHub;
    starHub.Create (1);

    NodeContainer starNodes;
    starNodes.Create (9);

    NodeContainer busNodes;
    busNodes.Create (10);

    InternetStackHelper internet;
    internet.Install (starHub);
    internet.Install (starNodes);
    internet.Install (busNodes);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
    p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

    for (uint32_t i = 0; i < starNodes.GetN (); i++) {
        NodeContainer pair (starHub.Get (0), starNodes.Get (i));
        p2p.Install (pair);
    }

    CsmaHelper csma;
    csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
    csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

    csma.Install (busNodes);

    NodeContainer bridge (starHub.Get (0), busNodes.Get (0));
    p2p.Install (bridge);

    AnimationInterface anim ("hybrid.xml");

    anim.SetConstantPosition (starHub.Get (0), 50, 50);

    for (uint32_t i = 0; i < starNodes.GetN (); i++) {
        anim.SetConstantPosition (starNodes.Get (i), 20 + i * 5, 80);
    }

    for (uint32_t i = 0; i < busNodes.GetN (); i++) {
        anim.SetConstantPosition (busNodes.Get (i), 20 + i * 7, 20);
    }

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}

