/*
 * ndnSimpleProvider.cc
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
#include "ndnSimpleProvider.h"

namespace inet
{
Define_Module(ndnSimpleProvider);

void ndnSimpleProvider::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if(stage == INITSTAGE_LOCAL){
        pktLen = par("pktLen").intValue();
        pktNum = par("pktNum").intValue();
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

void ndnSimpleProvider::handleMessageWhenUp(cMessage *msg){
    if (msg->isSelfMessage())
        handleSelfMessage(msg);
    else {
        currentSocket->processMessage(msg);
    }
    if (operationalState == State::STOPPING_OPERATION )
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void ndnSimpleProvider::handleSelfMessage(cMessage *msg)
{
    if(msg == start)
    {
        while(content < pktNum)
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

void ndnSimpleProvider::socketDataArrived(ndnSocket *socket, Packet *packet)
{

}

void ndnSimpleProvider::socketClosed(ndnSocket *socket)
{
   delete currentSocket;
   currentSocket = nullptr;
}

void ndnSimpleProvider::handleStartOperation(LifecycleOperation *operation)
{
    if (isEnabled())
    {
        currentSocket = new ndnSocket(&Protocol::nfd, gate("socketOut"));
        currentSocket->bind(&Protocol::nfd, nid, localPort);
        currentSocket->setCallback(this);
        scheduleAt(startTime, start);
    }
}

void ndnSimpleProvider::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

}

void ndnSimpleProvider::generateAndCacheData(const iName &interest){
    Packet* pkt = new Packet("data");
    auto payload = makeShared<ByteCountChunk>(B(pktLen));
    pkt->insertAtBack(payload);
    currentSocket->cacheData(interest, pkt);
}

bool ndnSimpleProvider::isEnabled()
{
    return true;
}

void ndnSimpleProvider::finish()
{
    ApplicationBase::finish();
    delete start;
}

void ndnSimpleProvider::handleStopOperation(LifecycleOperation *operation)
{

}

void ndnSimpleProvider::handleCrashOperation(LifecycleOperation *operation)
{

}

} // namespace inet


