/*
 * UdpResponse.cc
 *
 */

#include "inet/applications/compUdpApp/UdpResponse.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/common/L4PortTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/compUdpApp/reuqest_m.h"

namespace inet {

Define_Module(UdpResponse);

simsignal_t UdpResponse::reqStreamBytesSignal = registerSignal("reqStreamBytes"); //define signal

UdpResponse::~UdpResponse()
{
}

void UdpResponse::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        sendInterval = &cSimulation::getActiveSimulation()->getSystemModule()->par("sendInterval");
        rngNum = cSimulation::getActiveSimulation()->getSystemModule()->par("rngNum").intValue();
        packetLen = &par("packetLen");
        localPort = par("localPort");

        // statistics
        numPkSent = 0;
    }
}

void UdpResponse::finish()
{
}

void UdpResponse::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        // timer for a particular stream expired, send packet
//        sendReply(msg);
    }
    else
        socket.processMessage(msg);
}

void UdpResponse::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processStreamRequest(packet);
}

void UdpResponse::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpResponse::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void UdpResponse::processStreamRequest(Packet *msg)
{
    auto reqHead = msg->peekAtFront<Req>();

    // generate and send a packet
    Packet *pkt = new Packet("PacketStrmPk");
    long pktLen = *packetLen;

    pkt->setTimestamp(simTime());
    const auto& payload = makeShared<ByteCountChunk>(B(pktLen));
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());

    const auto& dataHead = makeShared<Reply>();
    dataHead->setSeq(reqHead->getSeq());
    dataHead->setCreateTime(simTime().dbl());

    pkt->insertAtBack(dataHead);
    pkt->insertAtBack(payload);

    emit(packetSentSignal, pkt);

    socket.sendTo(pkt, msg->getTag<L3AddressInd>()->getSrcAddress(), msg->getTag<L4PortInd>()->getSrcPort());
    msg->trim();
    delete msg;
}

void UdpResponse::sendReply(cMessage *timer, simtime_t timeStamp, int seq)
{
}

void UdpResponse::clearStreams()
{
}

void UdpResponse::handleStartOperation(LifecycleOperation *operation)
{
    socket.setOutputGate(gate("socketOut"));
    socket.setCallback(this);
    socket.bind(localPort);

    int timeToLive = par("timeToLive");
    if (timeToLive != -1)
        socket.setTimeToLive(timeToLive);

    int dscp = par("dscp");
    if (dscp != -1)
        socket.setDscp(dscp);

    int tos = par("tos");
    if (tos != -1)
        socket.setTos(tos);
}

void UdpResponse::handleStopOperation(LifecycleOperation *operation)
{
    clearStreams();
    socket.setCallback(nullptr);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void UdpResponse::handleCrashOperation(LifecycleOperation *operation)
{
    clearStreams();
    if (operation->getRootModule() != getContainingNode(this))     // closes socket when the application crashed only
        socket.destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    socket.setCallback(nullptr);
}

} // namespace inet
