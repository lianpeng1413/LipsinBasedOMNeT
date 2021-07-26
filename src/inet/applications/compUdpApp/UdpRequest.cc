/*
 * UdpRequest.cc
 */

#include <algorithm>
#include <fstream>

#include "inet/applications/compUdpApp/UdpRequest.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/compUdpApp/reuqest_m.h"

namespace inet
{
using std::string;
Define_Module(UdpRequest);

void UdpRequest::SimRecorder::ConsumerPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "sendNum: " << requestSendNum << endl;
    os << "recvNum: " << DataRecvNum << endl;
    if (requestSendNum != 0)
        os << "trans ratio: " << 100 * double(DataRecvNum) / requestSendNum << "%" << endl;  //success trans ratio.
    os << "send Interval: " << owner->sendInterval << "s" << endl;
    os << "Throughput: " << throughput.get() * 8 / ((simTime().dbl() - owner->startTime) * 1000 * 1000) << " Mbps" << endl;
    os << "Average delay: ";
    double sum = 0;
    if (delayArray.size() > 0)
    {
        std::for_each(delayArray.begin(), delayArray.end(), [&sum](double value) { sum += value; });
        os << sum * 1000/ delayArray.size() << " ms" << endl;
    }
    else
        os << 0 << "ms" << endl;
    os << endl;
}

void UdpRequest::SimRecorder::ProviderPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "requestRecvNum: " << requestRecvNum << endl;
    os << endl;
}

UdpRequest::~UdpRequest()
{
    finish();
    cancelAndDelete(selfMsg);
    cancelAndDelete(timer);
}


void UdpRequest::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL)
    {
        selfMsg = new cMessage("UDPRequestStart");
        timer = new cMessage("timer");
        Recorder.nodeName = getParentModule()->getName();
        Recorder.owner = this;
        startTime = par("startTime").doubleValue();
        sendInterval = cSimulation::getActiveSimulation()->getSystemModule()->par("sendInterval").doubleValue();
        helloInterval = par("helloInterval").intValue();
        path = par("RSpath").stdstringValue();
        packetName = par("packetName").stdstringValue();
    }
}

void UdpRequest::finish()
{
    std::ofstream outfile;
    auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() + std::string("_") +
                    std::to_string(this->getHelloInterval()) + std::string("_Consumer.txt");
    outfile.open(path + fileName, std::ofstream::app);
    Recorder.ConsumerPrint(outfile);
    outfile.close();

    ApplicationBase::finish();
}

void UdpRequest::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (msg == selfMsg){
            requestStream();  //send request packet
            scheduleAt(simTime() + sendInterval, timer);
        }
        else if (msg == timer)
        {
            sendReq();
            scheduleAt(simTime() + sendInterval, timer); //send request packet periodic
        }
    }
    else
        socket.processMessage(msg);
}

void UdpRequest::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    receiveStream(packet);
}

void UdpRequest::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpRequest::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void UdpRequest::sendReq()
{
    int svrPort = par("serverPort");
    const char *address = par("serverAddress");
    L3Address svrAddr = L3AddressResolver().resolve(address);
    Packet *pk = new Packet(std::string(packetName+"_"+std::to_string(seqNum)).c_str());

    const auto& head = makeShared<Req>();
    head->setSeq(seqNum);
        
    pk->setTimestamp(simTime());

    pk->insertAtBack(head);
    socket.sendTo(pk, svrAddr, svrPort);
    Recorder.requestSendNum++;
        
    delayMap[seqNum] = simTime().dbl();
    seqNum++;
}

void UdpRequest::requestStream()
{
    int svrPort = par("serverPort");
    int localPort = par("localPort");
    const char *address = par("serverAddress");
    L3Address svrAddr = L3AddressResolver().resolve(address);

    if (svrAddr.isUnspecified())
    {
        EV_ERROR << "Server address is unspecified, skip sending video stream request\n";
        return;
    }
    EV_INFO << "Requesting video stream from " << svrAddr << ":" << svrPort << "\n";

    socket.setOutputGate(gate("socketOut"));
    socket.bind(localPort);
    socket.setCallback(this);
    sendReq();
}

void UdpRequest::receiveStream(Packet *pk)
{
    const auto& datahead = pk->peekAtFront<Reply>();

    Recorder.DataRecvNum++;
    Recorder.delayArray.push_back(simTime().dbl() - delayMap[datahead->getSeq()]);
    Recorder.last = simTime();
    Recorder.throughput += B(pk->getByteLength());
    Recorder.tempThput += pk->getByteLength() * 8;

    EV_INFO << "Video stream packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
//    std::cout << "Video stream packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    emit(packetReceivedSignal, pk);
    pk->trim();
    delete pk;
}

void UdpRequest::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t startTimePar = par("startTime");
    simtime_t startTime = std::max(startTimePar, simTime());
    scheduleAt(startTime, selfMsg);
}

void UdpRequest::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void UdpRequest::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    if (operation->getRootModule() != getContainingNode(this)) // closes socket when the application crashed only
        socket.destroy();                                      //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
}

} // namespace inet
