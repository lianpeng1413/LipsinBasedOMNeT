/*
 * UdpFlowTransApp.cc
 *
 *  Created on: Mar 28, 2021
 *      Author: zeus_yf
 */

#include <algorithm>
#include <fstream>

#include "inet/applications/compUdpApp/UdpFlowTransApp.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/compUdpApp/flowHead_m.h"

namespace inet{

using std::string;
Define_Module(UdpFlowTransApp);

void UdpFlowTransApp::SimRecorder::ConsumerPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "sendNum: " << owner->seq + 1 << endl;
    os << "recvNum: " << DataRecvNum << endl;
    if (requestSendNum != 0)
        os << "trans ratio: " << 100 * double(DataRecvNum) / (owner->seq + 1) << "%" << endl;
    os << "send Interval: " << owner->sendInterval << "s" << endl;

    // file size = 2k = 10240*2
    os << "Throughput: " << 20480 * 8 * DataRecvNum / ((simTime().dbl() - owner->startTime) * 1000 * 1000) << " Mbps" << endl;
    os << "Average delay: ";
    double sum = 0;
    if (delayArray.size() > 0)
    {
        std::for_each(delayArray.begin(), delayArray.end(), [&sum](double value) { sum += value; });
        os << sum * 1000 / delayArray.size() << " ms" << endl;
    }
    else
        os << 0 << "ms" << endl;
    os << endl;
}

void UdpFlowTransApp::SimRecorder::ProviderPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "requestRecvNum: " << requestRecvNum << endl;
    os << endl;
}

void UdpFlowTransApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL)
    {
        selfMsg = new cMessage("UDPVideoStreamStart");
        timer = new cMessage("timer");
        timeout = new cMessage("timeout");
        Recorder.nodeName = getParentModule()->getName();
        Recorder.owner = this;
        startTime = par("startTime").doubleValue();
        sendInterval = cSimulation::getActiveSimulation()->getSystemModule()->par("sendInterval").doubleValue();
        greedy = par("greedy").boolValue();
        path = par("RSpath").stdstringValue();
        flowNum = par("flowNum").intValue();
    }
}

void UdpFlowTransApp::finish()
{
    ApplicationBase::finish();
    std::ofstream outfile;
    auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() + std::string("_Consumer.txt");
    outfile.open(path + fileName, std::ofstream::app);
    Recorder.ConsumerPrint(outfile);
    outfile.close();
}

void UdpFlowTransApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (msg == selfMsg)
        {
            bindSocket();
            requestFile();
            Recorder.delay = simTime();
            scheduleAt(simTime() + sendInterval, timer);
            scheduleAt(simTime() + limit, timeout);
        }

        else if (msg == timer)
        {
            requestFile();
            scheduleAt(simTime() + sendInterval, timer);
        }
        else if (msg == timeout)
        {
            moveOn();
            requestFile();
        }
    }
        else
            socket.processMessage(msg);
    }

void UdpFlowTransApp::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    receiveFile(packet);
}

void UdpFlowTransApp::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpFlowTransApp::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void UdpFlowTransApp::bindSocket()
{
    int localPort = par("localPort");
    socket.setOutputGate(gate("socketOut"));
    socket.bind(localPort);
    socket.setCallback(this);
}

void UdpFlowTransApp::requestFile()
{
    int svrPort = par("serverPort");

    const char *address = par("serverAddress");
    L3Address svrAddr = L3AddressResolver().resolve(address);

    if (svrAddr.isUnspecified())
    {
        EV_ERROR << "Server address is unspecified, skip sending video stream request\n";
        return;
    }

    EV_INFO << "Requesting video stream from " << svrAddr << ":" << svrPort << "\n";

    Recorder.requestSendNum++;

    Packet *pk = new Packet("FileReq");
    pk->setTimestamp(simTime());
    const auto &head = makeShared<FlowReq>();
    head->setSeq(seq);
    head->setOffset(seqToOffset[seq]);

    pk->insertAtBack(head);
    socket.sendTo(pk, svrAddr, svrPort);
}

void UdpFlowTransApp::receiveFile(Packet *pk)
{
    EV_INFO << "Video stream packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    std::cout << "Video stream packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;

    const auto &datahead = pk->peekAtFront<FlowData>();

    uint32_t fragNum;
    auto seq = datahead->getSeq();
    if (datahead->getTotalLenth() % (1000 - 20 - 8 -12) == 0)
        fragNum = datahead->getTotalLenth() / (1000 - 20 - 8 -12);
    else
        fragNum = datahead->getTotalLenth() / (1000 - 20 - 8 -12) + 1;
    uint32_t highbit = (~(1 << (32 - fragNum))) << fragNum;  //??TODO
    seqToOffset[seq] |= highbit;

    seqToOffset[seq] |= (1 << datahead->getOffset());
    auto test = seqToOffset[seq];

    if (~seqToOffset[seq] == 0 && recieveSET.find(seq) == recieveSET.end())
    {
        Recorder.DataRecvNum++;
        Recorder.throughput += B(datahead->getTotalLenth());
        Recorder.delayArray.push_back(simTime().dbl() - Recorder.delay.dbl());
        recieveSET.insert(seq);

        if (greedy)
        {
            moveOn();
            requestFile();
        }
    }
    pk->trim();
    delete pk;
}

void UdpFlowTransApp::moveOn()
{
    seq++;
    NowOffset = 0;
    pktSize = B(0);
    //        Recorder.delayArray.push_back(simTime().dbl() - Recorder.delay.dbl());
    Recorder.delay = simTime();
    cancelEvent(timeout);
    scheduleAt(simTime() + limit, timeout);
    cancelEvent(timer);
    scheduleAt(simTime() + sendInterval, timer);
}

void UdpFlowTransApp::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t startTimePar = par("startTime");
    simtime_t startTime = std::max(startTimePar, simTime());
    scheduleAt(startTime, selfMsg);
}

void UdpFlowTransApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void UdpFlowTransApp::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    if (operation->getRootModule() != getContainingNode(this)) // closes socket when the application crashed only
        socket.destroy();                                      //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
}

} // namespace inet




