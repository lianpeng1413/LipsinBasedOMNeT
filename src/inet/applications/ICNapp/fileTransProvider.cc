/*
 * fileTransProvider.cc
 *
 *  Created on: May 18, 2020
 *      Author: hiro
 */

#include <algorithm>
#include <fstream>

#include "inet/applications/ICNapp/fileTransProvider.h"
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

namespace inet
{
Define_Module(fileTransProvider);

void fileTransProvider::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if(stage == INITSTAGE_LOCAL){
        pktLen = par("pktLen").intValue();
        startTime = par("startTime").doubleValue();
        localPort = par("port").intValue();
        start = new cMessage("start");
        pPrefix = par("prefix").stdstringValue();

        nodeName = getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node += str;
        nid.set("nodeName", "prefix", node);

        filesSize = &par("fileSize");
        fileSize = filesSize->doubleValue();//unit B.
        sFragNum = fileSize / 1000; // fragments number of file
    }
}

void fileTransProvider::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
        handleSelfMessage(msg);
    else {
        currentSocket->processMessage(msg);
    }
    if (operationalState == State::STOPPING_OPERATION )
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void fileTransProvider::handleSelfMessage(cMessage *msg)
{
    if(msg == start)
    {//Generate content name.
        while(content < sFragNum)
        {
            std::string tag, prefix, tail;
            tag.append("1");
            prefix.append(pPrefix);
            tail.append(std::to_string(content));
            iName interestName;
            interestName.set(tag, prefix, tail);
            generateAndCacheData({interestName});
            content++;
        }
    }
}

void fileTransProvider::socketDataArrived(ndnSocket *socket, Packet *packet)
{
    packet->trim();
    delete packet;
}

void fileTransProvider::socketClosed(ndnSocket *socket)
{
    currentSocket->close();
    delete currentSocket;
    currentSocket = nullptr;
}

void fileTransProvider::handleStartOperation(LifecycleOperation *operation)
{
    currentSocket = new ndnSocket(&Protocol::NFD, gate("socketOut"));
    currentSocket->bind(&Protocol::NFD,nid, localPort);
    currentSocket->setCallback(this);
    scheduleAt(startTime, start);
}

void fileTransProvider::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();
}

void fileTransProvider::generateAndCacheData(const iName &interest)
{
    std::cout << getParentModule()->getName() << ", generate data with name: " << interest.str() << ", at" << simTime() << endl;
    Packet* pkt = new Packet("data");
    auto payload = makeShared<ByteCountChunk>(B(pktLen));
    pkt->insertAtBack(payload);
    currentSocket->cacheData(interest, pkt);
}

void fileTransProvider::finish()
{
    ApplicationBase::finish();
    delete start;
}

void fileTransProvider::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(start);
    currentSocket->setCallback(nullptr);
    currentSocket->close();
}

void fileTransProvider::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(start);
    if (operation->getRootModule() != getContainingNode(this))
        currentSocket->destroy();
    currentSocket->setCallback(nullptr);
}

}



