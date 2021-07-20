/*
 * ndnFlowTransApp.cc
 *
 *  Created on: Mar 28, 2021
 *      Author: zeus_yf
 */

#include <algorithm>
#include <fstream>

#include "inet/applications/ICNapp/ndnFlowTransApp.h"
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
Define_Module(ndnFlowTransApp);

void ndnFlowTransApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if(stage == INITSTAGE_LOCAL){
        pktLen = par("pktLen").intValue();
        fileNum =par("fileNum").intValue();
        startTime = par("startTime").doubleValue();
        localPort = par("port").intValue();
        start = new cMessage("start");
        pPrefix = par("prefix").stdstringValue();

        nodeName = getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node += str;
        nid.set("nodeName", "prefix", node);
    }
}

void ndnFlowTransApp::handleMessageWhenUp(cMessage *msg){
    if (msg->isSelfMessage())
        handleSelfMessage(msg);
    else {
        currentSocket->processMessage(msg);
    }
    if (operationalState == State::STOPPING_OPERATION )
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void ndnFlowTransApp::handleSelfMessage(cMessage *msg)
{
    if(msg == start)
    {
        while(content < fileNum)
        {
            std::string tag, prefix, tail;
            tag.append("interest");
            prefix.append(pPrefix);
            tail.append(std::to_string(content));
            iName interestName;
            interestName.set(tag, prefix, tail);
            generateAndCacheData({interestName});
            content++;
        }
    }
}

void ndnFlowTransApp::socketDataArrived(ndnSocket *socket, Packet *packet)
{
    // Recorder.delayArray.push_back((simTime().dbl() - Recorder.Delays[sid].dbl()) * 1000);
    // std::cout << "receive the packet successfully!" << endl;
    // std::cout << "delay is " << (simTime().dbl() - Recorder.Delays[sid].dbl()) * 1000 << " ms" << endl;
}

void ndnFlowTransApp::socketClosed(ndnSocket *socket)
{
   delete currentSocket;
   currentSocket = nullptr;
}

void ndnFlowTransApp::handleStartOperation(LifecycleOperation *operation)
{
    currentSocket = new ndnSocket(&Protocol::NFD, gate("socketOut"));
    currentSocket->bind(&Protocol::NFD,nid, localPort);
    currentSocket->setCallback(this);
    scheduleAt(startTime, start);
}

void ndnFlowTransApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();
}

void ndnFlowTransApp::generateAndCacheData(const iName &interest)
{
    Packet* pkt = new Packet("data");
    auto payload = makeShared<ByteCountChunk>(B(pktLen));
    pkt->insertAtBack(payload);
    currentSocket->cacheData(interest,pkt);
}

void ndnFlowTransApp::finish()
{
    ApplicationBase::finish();
    delete start;
}

void ndnFlowTransApp::handleStopOperation(LifecycleOperation *operation)
{
}

void ndnFlowTransApp::handleCrashOperation(LifecycleOperation *operation)
{
}

}



