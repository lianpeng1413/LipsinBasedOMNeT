/*
 * ndnFlowProvider.cc
 *
 *  Created on: Mar 28, 2021
 *      Author: zeus_yf
 */

#include <algorithm>
#include <fstream>

#include "inet/applications/ICNapp/ndnFlowProvider.h"
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
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/applications/common/SocketTag_m.h"

namespace inet
{
Define_Module(ndnFlowProvider);

void ndnFlowProvider::SimRecorder::ConsumerPrint(std::ostream &os)
{
    os << "index:    " << owner->nid.str() << endl;
    os << "sendNum: " << owner->content + 1 << endl;
    os << "recvNum: " << DataRecvNum << endl;
    if (InterestSendNum != 0)
        os << "trans ratio: " << 100 * double(DataRecvNum) / (owner->content + 1) << "%" << endl;
    os << "send Interval: " << owner->sendInterval << "s" << endl;
    os << "Throughput: " << throughput.get() * 8 / ((simTime().dbl() - owner->startTime.dbl()) * 1000 * 1000) << " Mbps" << endl;
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

void ndnFlowProvider::SimRecorder::ProviderPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "requestRecvNum: " << requestRecvNum << endl;
    os << endl;
}

void ndnFlowProvider::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        destIndex = par("destAddr").intValue();
        requestNum = par("requestNum").intValue();
        sendInterval = par("sendInterval").doubleValue();
        startTime = par("startTime").doubleValue();
        stopTime = par("stopTime").doubleValue();
        timeout = new cMessage("timeout");
        reTimer = new cMessage("retimer");
        localPort = par("port").intValue();
        path = par("RSpath").stdstringValue();
        Recorder.owner = this;
        start = new cMessage("start");
        rngNum = cSimulation::getActiveSimulation()->getSystemModule()->par("rngNum").intValue();
        cPrefix = par("prefix").stdstringValue();

        limit = par("limit").doubleValue();
        retransTimer = par("retransTimer").doubleValue();

        int nodeIndex = getParentModule()->getIndex();
        const char* nodeName = getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node.append(str);
        nid.set("nodeName", "prefix", node);
    }
}

void ndnFlowProvider::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
        handleSelfMessage(msg);
    else
    {
        currentSocket->processMessage(msg);
    }
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void ndnFlowProvider::handleSelfMessage(cMessage *msg)
{
    std::string tag, prefix, tail;
    tag.append("interest");
    prefix.append(cPrefix);
    tail.append(std::to_string(content));
    iName interestName;
    interestName.set(tag, prefix, tail);

    if (msg == start)
    {
        Recorder.delay = simTime();
        sendRequest({interestName});
        scheduleAt(simTime() + retransTimer, reTimer);
        scheduleAt(simTime() + limit, timeout);
    }
    else if (msg == reTimer)
    {
        sendRequest({interestName});
        scheduleAt(retransTimer + simTime(), reTimer);
    }
    else if (msg == timeout)
    {
        content++;
        Recorder.delay = simTime();
        sendRequest({interestName});

        cancelEvent(reTimer);
        scheduleAt(simTime() + limit, timeout);
        scheduleAt(simTime() + retransTimer, reTimer);
    }
}

void ndnFlowProvider::socketDataArrived(ndnSocket *socket, Packet *packet)
{
    std::string tag, prefix, tail;
    tag.append("interest");
    prefix.append(cPrefix);
    tail.append(std::to_string(content));
    iName interestName;
    interestName.set(tag, prefix, tail);

    cancelEvent(reTimer);

    Recorder.DataRecvNum += 1;

    //throughput statistic
    Recorder.delayArray.push_back(simTime().dbl() - Recorder.delay.dbl());
    Recorder.delay = simTime();
    Recorder.throughput += B(packet->getByteLength());
    packet->trim();
    delete packet;

    if(true)
    {
        content++;
        Recorder.delay = simTime();
        sendRequest({interestName});
        
        cancelEvent(reTimer);
        cancelEvent(timeout);
        scheduleAt(simTime() + limit, timeout);
        scheduleAt(simTime() + retransTimer, reTimer);
    }
}

void ndnFlowProvider::socketClosed(ndnSocket *socket)
{
    delete currentSocket;
    currentSocket = nullptr;
}

void ndnFlowProvider::handleStartOperation(LifecycleOperation *operation)
{
    currentSocket = new ndnSocket(&Protocol::NFD, gate("socketOut"));
    currentSocket->bind(&Protocol::NFD, nid, localPort);
    currentSocket->setCallback(this);
    scheduleAt(startTime, start);
}

void ndnFlowProvider::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();
}

void ndnFlowProvider::sendRequest(const iName &interestName)
{
    currentSocket->sendInterest(interestName, localPort, sendInterval);
    Recorder.InterestSendNum++;
}

void ndnFlowProvider::finish()
{
    ApplicationBase::finish();
    cancelAndDelete(start);
    cancelAndDelete(reTimer);
    std::ofstream outfile;
    auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() + std::string("fileTrans.txt");
    outfile.open(path + fileName, std::ofstream::app);
    Recorder.ConsumerPrint(outfile);
    outfile.close();
}

void ndnFlowProvider::handleStopOperation(LifecycleOperation *operation)
{
}

void ndnFlowProvider::handleCrashOperation(LifecycleOperation *operation)
{
}

} // namespace inet



