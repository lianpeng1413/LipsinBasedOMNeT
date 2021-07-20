/*
 * fileProvider.cc
 *
 *  Created on: May 20, 2020
 *      Author: hiro
 */

#include "inet/applications/compUdpApp/UdpFileProvider.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/common/L4PortTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/compUdpApp/fileHead_m.h"

namespace inet {

Define_Module(UdpFileProvider);

UdpFileProvider::~UdpFileProvider()
{
    for (auto & elem : fileFragments)
        cancelAndDelete(elem.second.timer);
}

void UdpFileProvider::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        sendInterval = &cSimulation::getActiveSimulation()->getSystemModule()->par("sendInterval");
        sendIntervals = sendInterval->doubleValue();
        rngNum = cSimulation::getActiveSimulation()->getSystemModule()->par("rngNum").intValue();
        packetLen = &par("packetLen");
        localPort = par("localPort");
        filesSize = &par("fileSize");
        fileSize = filesSize->doubleValue();//unit B.
        sFragNum = fileSize / 1000; // fragments number of file
    }
}

void UdpFileProvider::finish()
{
}

void UdpFileProvider::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        // timer for a timer to send file fragments
        sendFileFragment(msg);
    }
    else
        socket.processMessage(msg);
}

void UdpFileProvider::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processFileRequest(packet);
}

void UdpFileProvider::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpFileProvider::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void UdpFileProvider::processFileRequest(Packet *msg)
{
    auto dest = msg->getTag<L3AddressInd>()->getSrcAddress();
    auto destPort = msg->getTag<L4PortInd>()->getSrcPort();
    auto reqHead = msg->peekAtFront<FileReq>();
    auto seqNum = reqHead->getSeq();

    //if the seqNum is 0 and client doesn't request before, generate file and send fragments.
    if((seqNum == 0) && (clientAddrs.find(dest) == clientAddrs.end())){
        std::cout << getParentModule()->getName() << ", receive request from: " <<  dest << ", at:" << simTime() << endl;
        generateFileSendSet(msg);
        clientAddrs.insert(dest);
    }
    else{//packet loss occurred, re-send fragment.
        sendFileData(seqNum, dest, destPort);
    }

    msg->trim();
    delete msg;
    numFiles++;
}

void UdpFileProvider::generateFileSendSet(Packet *msg)
{
    for(int i=0; i < sFragNum; i++){
        // Register file fragments...
        cMessage *timer = new cMessage("fileSendTimer");
        fileFragmentsData *d = &fileFragments[timer->getId()];
        d->timer = timer;
        d->clientAddr = msg->getTag<L3AddressInd>()->getSrcAddress();
        d->clientPort = msg->getTag<L4PortInd>()->getSrcPort();
        d->fragment = i;
        scheduleAt(simTime() + i*sendIntervals, timer);
    }
}

void UdpFileProvider::sendFileFragment(cMessage *timer)
{
    auto it = fileFragments.find(timer->getId());
    if (it == fileFragments.end())
        throw cRuntimeError("Model error: file not found for timer");

    //Get generated data info, and generate fileData header.
    fileFragmentsData *d = &(it->second);
    const auto& dataHead = makeShared<FileData>();
    dataHead->setSeq(d->fragment);
    dataHead->setTotalLenth(fileSize);
    long len = 1000;

    // Generate and send a packet
    Packet *pk = new Packet("FilePacket");
    const auto& payload = makeShared<ByteCountChunk>(B(len));
    pk->insertAtBack(dataHead);
    pk->insertAtBack(payload);
    emit(packetSentSignal, pk);

    socket.sendTo(pk, d->clientAddr, d->clientPort);

    std::cout << getParentModule()->getName() << ", send fragment: " << d->fragment << " to client: " << d->clientAddr << ", at:" << simTime() << endl;
    numPkSent++; // for statistics.
//    cancelAndDelete(timer);
//    removeFragment(timer->getId());
}

void UdpFileProvider::removeFragment(long int timerID)
{
    auto it = fileFragments.begin();
    while(it != fileFragments.end()){
        if(it->first == timerID){
            fileFragments.erase(it);
        }
        else
            it++;
    }
}

void UdpFileProvider::sendFileData(double seq, L3Address clientAddr, int clientPort)
{
    const auto& dataHead = makeShared<FileData>();
    dataHead->setSeq(seq);
    dataHead->setTotalLenth(fileSize);

    Packet *pk = new Packet("reSendFilePacket");
    long len = 1000;
    const auto& payload = makeShared<ByteCountChunk>(B(len));
    
    pk->insertAtBack(dataHead);
    pk->insertAtBack(payload);

    // generate and send a packet
    emit(packetSentSignal, pk);
    socket.sendTo(pk, clientAddr, clientPort);
    std::cout << getParentModule()->getName() << ", re-send fragment: " << seq << " to client: " << clientAddr << ", at:" << simTime() << endl;

    numPkSent++;
}

void UdpFileProvider::clearFiles()
{
    for (auto & elem : fileFragments)
        cancelAndDelete(elem.second.timer);
    fileFragments.clear();
}

void UdpFileProvider::handleStartOperation(LifecycleOperation *operation)
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

void UdpFileProvider::handleStopOperation(LifecycleOperation *operation)
{
    clearFiles();
    socket.setCallback(nullptr);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void UdpFileProvider::handleCrashOperation(LifecycleOperation *operation)
{
    clearFiles();
    if (operation->getRootModule() != getContainingNode(this))     // closes socket when the application crashed only
        socket.destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    socket.setCallback(nullptr);
}

} // namespace inet
