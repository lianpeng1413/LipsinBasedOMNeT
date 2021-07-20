/*
 * ndnSimpleApp.cc
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#include <algorithm>
#include <fstream>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Protocol.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/EchoPacket_m.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/common/IpProtocolId_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/applications/common/SocketTag_m.h"
#include "ndnSimpleApp.h"
#include "inet/networklayer/contract/ndn/Interest_m.h"
#include "inet/networklayer/contract/ndn/iData_m.h"

namespace inet
{
Define_Module(ndnSimpleApp);

void ndnSimpleApp::SimRecorder::consumerPrint(std::ostream &os)
{
    os << "index:    " << nodeNameOwn << endl;
    os << "sendNum: " << InterestSendNum << endl;
    os << "recvNum: " << DataRecvNum << endl;
    if (InterestSendNum != 0)
        os << "trans ratio: " << 100 * DataRecvNum / InterestSendNum << "%" << endl;
    os << "send Interval: " << owner->sendInterval << "s" << endl;
    os << "Throughput: " << throughput.get() * 8 / ((simTime().dbl() - owner->startTime.dbl()) * 1000 * 1000) << " Mbps" << endl;
    os << "Total Throughput: " << totalThroughput.get() * 8 / ((simTime().dbl() - owner->startTime.dbl()) * 1000 * 1000) << " Mbps" << endl;
    os << "Average delay: ";
    double sum = 0;
    if(delayArrary.size() > 0){
        std::for_each(delayArrary.begin(), delayArrary.end(), [&sum](double value) { sum += value; });
        os << sum / delayArrary.size() << " ms" << endl;
    }
    else
        os << 0 << "ms" << endl;
    os << endl;
}

void ndnSimpleApp::SimRecorder::providerPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "InterestRecvNum: " << InterestRecvNum << endl;
    os << endl;
}

ndnSimpleApp::~ndnSimpleApp()
{
}

void ndnSimpleApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if(stage == INITSTAGE_LOCAL){
        cPrefix = par("prefix").stdstringValue();
        requestNum = par("requestNum").intValue();
        sendInterval = par("sendInterval").doubleValue();
        startTime = par("startTime").doubleValue();
        stopTime = par("stopTime").doubleValue();
        timer = new cMessage("sendInterest");
        localPort = par("localPort").intValue();
        path=par("RSpath").stdstringValue();
        Recorder.owner = this;
        start = new cMessage("start");
        rngNum = cSimulation::getActiveSimulation()->getSystemModule()->par("rngNum").intValue();

        int nodeIndex = getParentModule()->getIndex();
        const char* nodeName = getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node.append(str);
        nid.set("nodeName", "prefix", node);
        Recorder.nodeNameOwn = getParentModule()->getName();
    }
}

void ndnSimpleApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
        handleSelfMessage(msg);
    else {
        currentSocket->processMessage(msg);
    }
    if (operationalState == State::STOPPING_OPERATION )
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void ndnSimpleApp::handleSelfMessage(cMessage *msg)
{
    if(msg == start)
    {
        std::string tag, prefix, tail;
        tag.append("1");
        prefix.append("1");
        tail.append(std::to_string(content));
        iName interestName;
        interestName.set(tag, prefix, tail);

        sendRequest(interestName);
        scheduleAt(simTime() + exponential(sendInterval, rngNum), timer);
        content++;
    }
    else if(msg == timer)
    {
        if(content < requestNum)
        {
            std::string tag, prefix, tail;
            tag.append("1");
            prefix.append("1");
            tail.append(std::to_string(content));
            iName interestName;
            interestName.set(tag, prefix, tail);

            content++;
            sendRequest(interestName);
            scheduleAt(simTime() + sendInterval, timer);
        }
        else{
            content = 0;
            scheduleAt(simTime(), timer);
        }
    }
}

void ndnSimpleApp::socketDataArrived(ndnSocket *socket, Packet *packet)
{
    //throughput statistic
    Recorder.throughput += B(packet->getByteLength());
    packet->trim();
    delete packet;
}

void ndnSimpleApp::socketClosed(ndnSocket *socket)
{
    currentSocket->close();
    delete currentSocket;
    currentSocket->setCallback(nullptr);
}

void ndnSimpleApp::handleStartOperation(LifecycleOperation *operation)
{
    currentSocket = new ndnSocket(&Protocol::NFD, gate("socketOut"));
    currentSocket->bind(&Protocol::NFD, nid, localPort);
    currentSocket->setCallback(this);
    scheduleAt(startTime, start);
}

void ndnSimpleApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();
}

void ndnSimpleApp::sendRequest(const iName &interest){
    currentSocket->sendInterest(interest, localPort, sendInterval);
    Recorder.InterestSendNum++;
}

void ndnSimpleApp::finish()
{
    ApplicationBase::finish();

//    std::ofstream outfile;
//    auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() + std::string("_Consumer.txt");
//    outfile.open(path + fileName, std::ofstream::app);
//    Recorder.consumerPrint(outfile);
//    outfile.close();

    cancelAndDelete(start);
    cancelAndDelete(timer);
}

void ndnSimpleApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(start);
    currentSocket->close();
}

void ndnSimpleApp::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(start);
    if (operation->getRootModule() != getContainingNode(this))     // closes socket when the application crashed only
        currentSocket->destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
}

}


