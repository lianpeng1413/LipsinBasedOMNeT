/*
 * UdpFlowProvider.cc
 *
 *  Created on: Mar 28, 2021
 *      Author: zeus_yf
 */

#include "inet/applications/compUdpApp/UdpFlowProvider.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/common/L4PortTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/compUdpApp/flowHead_m.h"

namespace inet {

Define_Module(UdpFlowProvider);

UdpFlowProvider::~UdpFlowProvider()
{

}

void UdpFlowProvider::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        sendInterval = &cSimulation::getActiveSimulation()->getSystemModule()->par("sendInterval");
        rngNum = cSimulation::getActiveSimulation()->getSystemModule()->par("rngNum").intValue();
        packetLen = &par("packetLen");
        videoSize = &par("videoSize");
        localPort = par("localPort");

        if((*videoSize).intValue() % (1000 -20 - 8 -12) != 0)
            pktNum = (*videoSize).intValue() / (1000 -20 - 8 -12) + 1;
        else pktNum = (*videoSize).intValue() / (1000 -20 - 8 -12);
        
        highBit = (~(1<<(32-pktNum)))<<pktNum;

        // statistics
        numStreams = 0;
        numPkSent = 0;
    }
}

void UdpFlowProvider::finish()
{
}

void UdpFlowProvider::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        // timer for a particular video stream expired, send packet
//        sendStreamData(msg);
    }
    else
        socket.processMessage(msg);
}

void UdpFlowProvider::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processStreamRequest(packet);
}

void UdpFlowProvider::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpFlowProvider::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void UdpFlowProvider::processStreamRequest(Packet *msg)
{
    auto dest = msg->getTag<L3AddressInd>()->getSrcAddress();
    auto destPort = msg->getTag<L4PortInd>()->getSrcPort();
    auto reqHead = msg->peekAtFront<FlowReq>();
    auto seqNum = reqHead->getSeq();

    if(reqHead->getOffset() == 0)
    {
        for(uint32_t i = 0; i<pktNum; i++)
        {
            sendFileData(i, seqNum, dest, destPort);
        }
    }
    else
    {
        uint32_t offset = reqHead->getOffset() == 0;
        for(uint32_t i = 0; i<pktNum; i++)
        {
            auto temp = (offset >> i);
            if(temp % 2 == 0)
                sendFileData(i, seqNum, dest, destPort);
        }
    }
    msg->trim();
    delete msg;
    numStreams++;
}

void UdpFlowProvider::sendFileData(uint32_t offset, int seq, L3Address clientAddr, int clientPort)
{
    const auto& dataHead = makeShared<FlowData>();
    dataHead->setSeq(seq);
    dataHead->setOffset(offset);
    dataHead->setTotalLenth((*videoSize).intValue());

    Packet *pk = new Packet("FILE");
    long len = 0;
    if(offset <pktNum-1)
        len = *packetLen;
    else len = (*videoSize).intValue() - (pktNum-1) * (*packetLen).intValue();
    const auto& payload = makeShared<ByteCountChunk>(B(len));
    
    pk->insertAtBack(dataHead);
    pk->insertAtBack(payload);

    // generate and send a packet
    emit(packetSentSignal, pk);
    socket.sendTo(pk, clientAddr, clientPort);
    numPkSent++;
}

void UdpFlowProvider::clearStreams()
{
}

void UdpFlowProvider::handleStartOperation(LifecycleOperation *operation)
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

void UdpFlowProvider::handleStopOperation(LifecycleOperation *operation)
{
    clearStreams();
    socket.setCallback(nullptr);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void UdpFlowProvider::handleCrashOperation(LifecycleOperation *operation)
{
    clearStreams();
    if (operation->getRootModule() != getContainingNode(this))     // closes socket when the application crashed only
        socket.destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    socket.setCallback(nullptr);
}

} // namespace inet




