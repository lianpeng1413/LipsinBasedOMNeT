/*
 * fileTransApp.cc
 */

#include <algorithm>
#include <fstream>

#include "inet/applications/ICNapp/fileTransApp.h"
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
#include "inet/applications/ICNapp/ndnFileHead_m.h"
#include "inet/networklayer/contract/ndn/iData_m.h"

namespace inet
{
Define_Module(fileTransApp);

void fileTransApp::SimRecorder::ConsumerPrint(std::ostream &os)
{
    os << "fileSize: " << owner->fileSize/1000000 <<  "MB" << endl;
    os << "index:    " << nodeName << endl;
    os << "sendNum: " << owner->requestNum << endl;
    os << "resendNum: " << owner->resendNum << endl;
    os << "Total interest send: " << InterestSendNum << endl;
    os << "recvNum: " << DataRecvNum << endl;
    os << "Average delay: " << owner->fileTransDelay * 1000 << " ms" << endl;
    os << endl;
}

void fileTransApp::SimRecorder::ProviderPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "requestRecvNum: " << requestRecvNum << endl;
    os << endl;
}

void fileTransApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        startTime = par("startTime").doubleValue();
        timeout = new cMessage("timeout");
        localPort = par("port").intValue();
        path = par("RSpath").stdstringValue();
        Recorder.owner = this;
        Recorder.nodeName = getParentModule()->getName();
        start = new cMessage("start");
        limit = par("limit").doubleValue();
        rngNum = cSimulation::getActiveSimulation()->getSystemModule()->par("rngNum").intValue();
        cPrefix = par("prefix").stdstringValue();
        sendInterval = par("sendInterval").doubleValue();
        syncInterval = par("syncInterval");
        timer = new cMessage("sendInterest");

        const char* nodeName = getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node.append(str);
        nid.set("nodeName", "prefix", node);

        filesSize = &par("fileSize");
        fileSize = filesSize->doubleValue();//unit B.
        sFragNum = fileSize / 1000; // fragments number of file
        for(int i = 0; i < sFragNum; i++){ //store the fragments
            dataFram.push_back(i);
        }
    }
}

void fileTransApp::handleMessageWhenUp(cMessage *msg)
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

void fileTransApp::handleSelfMessage(cMessage *msg)
{
    if (msg == start)
    {
        std::string tag, prefix, tail;
        tag.append("1");
        prefix.append(cPrefix);
        tail.append(std::to_string(dataFram[0]));
        iName interestName;
        interestName.set(tag, prefix, tail);

        Recorder.delay = simTime(); //Record current time.
        sendRequest({interestName});
        scheduleAt(simTime()+sendInterval, timer);
        content++;
        requestNum++;
    }
    else if(msg == timer)
    {
        if(content < sFragNum)
        {
            cancelEvent(timer);
            cancelEvent(timeout);
            std::string tag, prefix, tail;
            tag.append("1");
            prefix.append(cPrefix);
            tail.append(std::to_string(content));
            iName interestName;
            interestName.set(tag, prefix, tail);

            Recorder.Delays[interestName] = simTime();
            sendRequest({interestName});
            content++;
            requestNum++;
            scheduleAt(simTime() + sendInterval, timer);
            scheduleAt(simTime() + limit, timeout);
        }
    }
    else if (msg == timeout)
    {
        cancelEvent(timeout);
        if((dataFram.size() > 1) && (dataFram[1] - dataFram[0] >= 1)){
        //re-send request with the seqNo which is the first one in vector.
            std::string tag, prefix, tail;
            tag.append("1");
            prefix.append(cPrefix);
            tail.append(std::to_string(dataFram[0]));
            iName interestName;
            interestName.set(tag, prefix, tail);
            sendRequest({interestName});
            resendNum++;
            scheduleAt(simTime() + limit, timeout);
        }
    }
}

void fileTransApp::socketDataArrived(ndnSocket *socket, Packet *packet)
{
    Recorder.DataRecvNum += 1;

    const auto &pktHead = packet->peekAtFront<iData>();
    auto interestName = pktHead->getInterestName();
    std::string tail = interestName.getTail();
    long seqNum = std::atol(tail.c_str());
    std::cout << getParentModule()->getName() << " receive interest: " << interestName.str() <<  ", at: " << simTime() <<endl;

    //delete seqNum in vector.
    auto it = dataFram.begin();
    while (it != dataFram.end()) {
        if ((*it) == seqNum)
        {
            it = dataFram.erase(it); //delete it pointer
        }
        else {
            it++;
        }
    }
    recieveSET.insert(seqNum);

    if (dataFram.size() == 0 && recieveSET.size() == sFragNum)
    {
        Recorder.delayArray.push_back(simTime().dbl() - Recorder.delay.dbl());
        fileTransDelay = simTime().dbl() - Recorder.delay.dbl();
    }
    packet->trim();
    delete packet;
}

void fileTransApp::socketClosed(ndnSocket *socket)
{
    currentSocket->close();
    delete currentSocket;
    currentSocket->setCallback(nullptr);
}

void fileTransApp::handleStartOperation(LifecycleOperation *operation)
{
    currentSocket = new ndnSocket(&Protocol::NFD, gate("socketOut"));
    currentSocket->bind(&Protocol::NFD, nid, localPort);
    currentSocket->setCallback(this);
    scheduleAt(startTime, start);
}

void fileTransApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();
}

void fileTransApp::sendRequest(const iName &interestName)
{
    std::cout << getParentModule()->getName() << " send request interest: "<< interestName.str() << ", at: " << simTime() << endl;
    currentSocket->sendInterest(interestName, localPort, sendInterval);
    Recorder.InterestSendNum++;
}

void fileTransApp::finish()
{
    ApplicationBase::finish();
    cancelAndDelete(start);
    std::ofstream outfile;
    auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName()  + std::string("_") +
            std::to_string(this->getSyncInterval()) + std::string("_Consumer.txt");
    outfile.open(path + fileName, std::ofstream::app);
    Recorder.ConsumerPrint(outfile);
    outfile.close();
}

void fileTransApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(start);
    currentSocket->close();
}

void fileTransApp::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(start);
    if (operation->getRootModule() != getContainingNode(this))     // closes socket when the application crashed only
        currentSocket->destroy();
}

} // namespace inet
