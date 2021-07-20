/*
 * ndnSocket.cc
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#include "ndnSocket.h"

#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/packet/Message.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/ndn/ndnSocketCommand_m.h"

namespace inet{

ndnSocket::ndnSocket(const Protocol* protocol, cGate *outputGate) :
        l3Protocol(protocol),
        socketId(getEnvir()->getUniqueNumber()),
        outputGate(outputGate)
{
}

void ndnSocket::bind(const Protocol *protocol, const iName &nid, int localPort)
{
    auto node = outputGate->getOwnerModule()->getParentModule()->getFullPath();
    ASSERT(!bound);
    ASSERT(l3Protocol != nullptr);
    auto *command = new ndnSocketBindCommand();
    command->setProtocol(protocol);
    command->setNid(nid);
    command->setLocalPort(localPort);
    auto request = new Request("bind", NDN_C_BIND);
    request->setControlInfo(command);
    sendToOutput(request);
    bound = true;
    isOpen_ = true;
}

void ndnSocket::sendToOutput(cMessage *message)
{
    if (!outputGate)
        throw cRuntimeError("ndnSocket: setOutputGate() must be invoked before the socket can be used");
    auto& tags = getTags(message);
    tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(l3Protocol);
    tags.addTagIfAbsent<SocketReq>()->setSocketId(socketId);
    check_and_cast<cSimpleModule *>(outputGate->getOwnerModule())->send(message, outputGate);
}

void ndnSocket::setCallback(ndnSocket::ICallback *callback)
{
    this->callback = callback;
}

void ndnSocket::sendInterest(const iName &interest, int port, double inter)
{
    ASSERT(bound);
    ASSERT(l3Protocol != nullptr);
    auto *command = new ndnSocketSendInterestCommand();
    command->setInterest(interest);
    command->setLocalPort(port);
    command->setInter(inter);
    auto request = new Request("bind", NDN_C_SEND_INTEREST);
    request->setControlInfo(command);
    sendToOutput(request);
}

void ndnSocket::close()
{
    ASSERT(bound);
    auto *command = new ndnSocketCloseCommand();
    auto request = new Request("close", NDN_C_CLOSE);
    request->setControlInfo(command);
    sendToOutput(request);
}

void ndnSocket::destroy()
{
    ASSERT(bound);
    auto command = new ndnSocketDestroyCommand();
    auto request = new Request("destroy", NDN_C_DESTROY);
    request->setControlInfo(command);
    sendToOutput(request);
}

bool ndnSocket::belongsToSocket(cMessage *msg) const
{
    auto& tags = getTags(msg);
    int msgSocketId = tags.getTag<SocketInd>()->getSocketId();
    return socketId == msgSocketId;
}

void ndnSocket::processMessage(cMessage *msg)
{
    ASSERT(belongsToSocket(msg));
    if (callback)
        callback->socketDataArrived(this, check_and_cast<Packet *>(msg));
    else
        delete msg;
}

void ndnSocket::cacheData(const iName &interest, cMessage *msg)
{
    ASSERT(bound);
    ASSERT(l3Protocol != nullptr);
    auto *command = new ndnSocketCacheDataCommand();
    command->setInterest(interest);
    command->setPkt(msg);
    auto request = new Request("data", NDN_C_CACHE_DATA);
    request->setControlInfo(command);
    sendToOutput(request);
}

} // namespace inet


