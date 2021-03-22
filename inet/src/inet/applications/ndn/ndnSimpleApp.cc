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

namespace inet
{
Define_Module(ndnSimpleApp);

void ndnSimpleApp::SimRecorder::consumerPrint(std::ostream &os)
{
    os << "node name:    " << nodeName << endl;
    os << "sendNum: " << InterestSendNum << endl;
    os << "recvNum: " << DataRecvNum << endl;
    if (InterestSendNum != 0)
        os << "trans ratio: " << 100 * DataRecvNum / InterestSendNum << "%" << endl;
    os << "send Interval: " << owner->sendInterval << "s" << endl;
//    os << "Throughput: " << throughput.get() * 8 / ((simTime().dbl() - owner->startTime.dbl()) * 1000 * 1000) << " Mbps" << endl;
    os << "Throughput: " << throughput.get() * 8 / ((simTime().dbl() - owner->startTime )* 1000 * 1000) << " Mbps" << endl;

        os << "Average delay: " << (simTime().dbl() - owner->startTime ) << endl;
    double sum = 0;

    os << endl;
}

void ndnSimpleApp::SimRecorder::providerPrint(std::ostream &os)
{
    os << "node name:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "InterestRecvNum: " << InterestRecvNum << endl;
    os << endl;
}

void ndnSimpleApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if(stage == INITSTAGE_LOCAL){
        cPrefix = par("prefix").stdstringValue();
        destNodeName = par("destNodeName").stdstringValue();
        requestNum = par("requestNum").intValue();
        sendInterval = par("sendInterval").doubleValue();
        startTime = par("startTime").doubleValue();
        stopTime = par("stopTime").doubleValue();
        timer = new cMessage("sendInterest");
        localPort = par("port").intValue();
        path=par("RSTpath").stdstringValue();
        Recorder.owner = this;
        start = new cMessage("start");
        rngNum = cSimulation::getActiveSimulation()->getSystemModule()->par("rngNum").intValue();

        int nodeIndex = getParentModule()->getIndex();
        const char* nodeName = getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node.append(str);
        nid.set("nodeName", "prefix", node);
    }
}

void ndnSimpleApp::handleMessageWhenUp(cMessage *msg){
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
//        content++;//add
        std::string tag, prefix, tail;
        tag.append("interest");
        prefix.append(cPrefix);
        tail.append(std::to_string(content));
        iName interestName;
        interestName.set(tag, prefix, tail);

        sendRequest({interestName});
        scheduleAt(simTime()+sendInterval, timer);
    }
    else if(msg == timer)
    {
        if(content < requestNum)
        {
            std::string tag, prefix, tail;
            tag.append("interest");
            prefix.append(cPrefix);
            tail.append(std::to_string(content));
            iName interestName;
            interestName.set(tag, prefix, tail);

            content++;
            sendRequest({interestName});
            scheduleAt(simTime() + exponential(sendInterval, rngNum), timer);
        }
        else cancelEvent(timer);
    }
}

void ndnSimpleApp::socketDataArrived(ndnSocket *socket, Packet *packet)
{
    Recorder.DataRecvNum++;
    Recorder.throughput += B(packet->getByteLength());
    delete packet;
}

void ndnSimpleApp::socketClosed(ndnSocket *socket)
{

   delete currentSocket;
   currentSocket = nullptr;
}

void ndnSimpleApp::handleStartOperation(LifecycleOperation *operation)
{
    if (isEnabled())
    {
        currentSocket = new ndnSocket(&Protocol::nfd, gate("socketOut"));
        currentSocket->bind(&Protocol::nfd,nid, localPort);
        currentSocket->setCallback(this);
        scheduleAt(startTime, start);
    }
}

void ndnSimpleApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

}

void ndnSimpleApp::sendRequest(const iName &interest){
    currentSocket->sendInterest(interest, localPort, sendInterval);
    Recorder.InterestSendNum++;
}

bool ndnSimpleApp::isEnabled()
{
    return destIndex >= 0;
}

void ndnSimpleApp::finish()
{
    ApplicationBase::finish();

    std::ofstream outfile;
    auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() + std::string("_Consumer.txt");
    outfile.open(fileName, std::ofstream::app);
    Recorder.consumerPrint(outfile);
    outfile.close();
    delete start;
}

void ndnSimpleApp::handleStopOperation(LifecycleOperation *operation)
{

}

void ndnSimpleApp::handleCrashOperation(LifecycleOperation *operation)
{

}

}


