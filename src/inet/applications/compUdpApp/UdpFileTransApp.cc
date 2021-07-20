/*
 * fileTransApp.cc
 *
 *  Created on: May 20, 2020
 *      Author: hiro
 */

#include <algorithm>
#include <fstream>

#include "inet/applications/compUdpApp/UdpFileTransApp.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/compUdpApp/fileHead_m.h"

namespace inet{

using std::string;
Define_Module(UdpFileTransApp);

void UdpFileTransApp::SimRecorder::ConsumerPrint(std::ostream &os)
{
    os << "fileSize: " << owner->fileSize/1000000 <<  "MB" << endl;
    os << "index:    " << nodeName << endl;
    os << "sendNum: " << requestSendNum << endl;
    os << "resendNum: " << owner->reSendNum << endl;
    os << "recvNum: " << DataRecvNum << endl;
    os << "Average delay: " << owner->fileTransDelay * 1000 << " ms" << endl;
    os << endl;
}

void UdpFileTransApp::SimRecorder::ProviderPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "requestRecvNum: " << requestRecvNum << endl;
    os << endl;
}

void UdpFileTransApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL)
    {
        selfMsg = new cMessage("UDPFileTransStart");
        timeout = new cMessage("timeout");
        limit = par("limit").doubleValue();
        Recorder.nodeName = getParentModule()->getName();
        Recorder.owner = this;
        startTime = par("startTime").doubleValue();
        helloInterval = par("helloInterval").intValue();
        path = par("RSpath").stdstringValue();
        filesSize = &par("fileSize");
        fileSize = filesSize->doubleValue();//unit B.
        sFragNum = fileSize / 1000; // fragments number of file
        for(int i = 0; i < sFragNum; i++){ //store the fragments
            dataFram.push_back(i);
        }
    }
}

void UdpFileTransApp::finish()
{
    ApplicationBase::finish();
    std::ofstream outfile;
    auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName()  + std::string("_") +
            std::to_string(this->getHelloInterval()) + std::string("_Consumer.txt");
    outfile.open(path + fileName, std::ofstream::app);
    Recorder.ConsumerPrint(outfile);
    outfile.close();
}

void UdpFileTransApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (msg == selfMsg)
        {
            bindSocket();
            requestFile(dataFram[0]); //send the first fragment.
            Recorder.delay = simTime();
            Recorder.requestSendNum++;
            scheduleAt(simTime() + limit, timeout);
        }
        else if (msg == timeout)
        {
            if((dataFram.size() > 1) && (dataFram[1] - dataFram[0] >= 1)){
                requestFile(dataFram[0]);//re-send request with the seqNo which is the first one in vector.
                reSendNum++;
                scheduleAt(simTime() + limit, timeout);
            }
        }
    }
        else
            socket.processMessage(msg);
    }

void UdpFileTransApp::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    receiveFile(packet);
}

void UdpFileTransApp::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpFileTransApp::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void UdpFileTransApp::bindSocket()
{
    int localPort = par("localPort");
    socket.setOutputGate(gate("socketOut"));
    socket.bind(localPort);
    socket.setCallback(this);
}

void UdpFileTransApp::requestFile(double seqNo)
{
    int svrPort = par("serverPort");
    const char *address = par("serverAddress");
    L3Address svrAddr = L3AddressResolver().resolve(address);
    if (svrAddr.isUnspecified()) {
        EV_ERROR << "Server address is unspecified, skip sending file request\n";
        return;
    }

    //Generate packet with file request header(size:16B)
    Packet *pk = new Packet("FileReq");
    pk->setTimestamp(simTime());
    const auto &head = makeShared<FileReq>();
    seq = seqNo;        //get the first fragment num for the first request.
    head->setSeq(seq);  //set sequence num.

    pk->insertAtBack(head);
    socket.sendTo(pk, svrAddr, svrPort);

    std::cout  << getParentModule()->getName() << " Requesting file from " << svrAddr << ": " << seq << ", at: "<< simTime() << "\n";
}

void UdpFileTransApp::receiveFile(Packet *pk)
{
    EV_INFO << "packet received: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
//    std::cout << "packet received: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    Recorder.DataRecvNum++;
    const auto &datahead = pk->peekAtFront<FileData>();
    auto seq = datahead->getSeq();

    //delete seqNum in vector.
    auto it = dataFram.begin();
    while (it != dataFram.end()) {
        if ((*it) == seq)
        {
            it = dataFram.erase(it); //delete it pointer
        }
        else {
            it++;
        }
    }
    recieveSET.insert(seq);

    if (dataFram.size() == 0 && recieveSET.size() == sFragNum)
    {
        Recorder.delayArray.push_back(simTime().dbl() - Recorder.delay.dbl());
        fileTransDelay = simTime().dbl() - Recorder.delay.dbl();
    }
    pk->trim();
    delete pk;
}

void UdpFileTransApp::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t startTimePar = par("startTime");
    simtime_t startTime = std::max(startTimePar, simTime());
    scheduleAt(startTime, selfMsg);
}

void UdpFileTransApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void UdpFileTransApp::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    if (operation->getRootModule() != getContainingNode(this)) // closes socket when the application crashed only
        socket.destroy();                                      //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
}

} // namespace inet
