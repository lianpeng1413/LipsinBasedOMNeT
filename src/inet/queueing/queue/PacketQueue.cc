//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "inet/common/ModuleAccess.h"
#include "inet/common/Simsignals.h"
#include "inet/queueing/function/PacketComparatorFunction.h"
#include "inet/queueing/function/PacketDropperFunction.h"
#include "inet/queueing/queue/PacketQueue.h"

namespace inet {
namespace queueing {
Register_Abstract_Class(CongestionChangeDetails);
Define_Module(PacketQueue);

std::string CongestionChangeDetails::str() const
{
    std::stringstream out;
    out << obj->getFullPath() << " changed congestionState: " << congestionState << "\n";
    return out.str();
}
void PacketQueue::initialize(int stage)
{
    PacketQueueBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        queue.setName("storage");
        inputGate = gate("in");
        congestionCheck = par("congestionCheck");
        producer = findConnectedModule<IActivePacketSource>(inputGate);
        outputGate = gate("out");
        collector = findConnectedModule<IActivePacketSink>(outputGate);
        packetCapacity = par("packetCapacity");
        dataCapacity = b(par("dataCapacity"));
        buffer = getModuleFromPar<IPacketBuffer>(par("bufferModule"), this, false);
        packetComparatorFunction = createComparatorFunction(par("comparatorClass"));
        if (packetComparatorFunction != nullptr)
            queue.setup(packetComparatorFunction);
        packetDropperFunction = createDropperFunction(par("dropperClass"));
    }
    else if (stage == INITSTAGE_QUEUEING) {
        checkPushPacketSupport(inputGate);
        checkPopPacketSupport(outputGate);
        if (producer != nullptr)
            producer->handleCanPushPacket(inputGate);
    }
    else if (stage == INITSTAGE_LAST)
        updateDisplayString();
}

IPacketDropperFunction *PacketQueue::createDropperFunction(const char *dropperClass) const
{
    if (strlen(dropperClass) == 0)
        return nullptr;
    else
        return check_and_cast<IPacketDropperFunction *>(createOne(dropperClass));
}

IPacketComparatorFunction *PacketQueue::createComparatorFunction(const char *comparatorClass) const
{
    if (strlen(comparatorClass) == 0)
        return nullptr;
    else
        return check_and_cast<IPacketComparatorFunction *>(createOne(comparatorClass));
}

void PacketQueue::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    pushPacket(packet, packet->getArrivalGate());
}

bool PacketQueue::isOverloaded() const
{
    return (packetCapacity != -1 && getNumPackets() > packetCapacity) ||
           (dataCapacity != b(-1) && getTotalLength() > dataCapacity);
}

int PacketQueue::getNumPackets() const
{
    return queue.getLength();
}

Packet *PacketQueue::getPacket(int index) const
{
    if (index < 0 || index >= queue.getLength())
        throw cRuntimeError("index %i out of range", index);
    return check_and_cast<Packet *>(queue.get(index));
}
void PacketQueue::congestionCheckandEmitSignal()
{
    bool isChanged = false;
    if(packetCapacity == -1) return;
    double ratio = ((double)getNumPackets())/packetCapacity;
    if(ratio <= 0.2){
        if(occupancy != 0) isChanged = true;
        occupancy = 0;
    }else if(ratio <= 0.4){
        if(occupancy != 1) isChanged = true;
        occupancy = 1;
    }else if(ratio <= 0.6){
        if(occupancy != 2) isChanged = true;
        occupancy = 2;
    }else if(ratio <= 0.8){
        if(occupancy != 3) isChanged = true;
        occupancy = 3;
    }else{
        if(occupancy != 4) isChanged = true;
        occupancy = 4;
    }
    if(isChanged){
        cObject *ethernetPtr = this->getOwner()->getOwner();
        CongestionChangeDetails changeDetails(ethernetPtr,occupancy);
        emit(congestionChangedSignal,&changeDetails);
    }

}
void PacketQueue::pushPacket(Packet *packet, cGate *gate)
{
    if(congestionCheck) congestionCheckandEmitSignal();
    Enter_Method("pushPacket");
    EV_INFO << "Pushing packet " << packet->getName() << " into the queue." << endl;
    queue.insert(packet);
    emit(packetPushedSignal, packet);
    if (buffer != nullptr)
        buffer->addPacket(packet);
    else if (isOverloaded()) {
        if (packetDropperFunction != nullptr) {
            while (!isEmpty() && isOverloaded()) {
                auto packet = packetDropperFunction->selectPacket(this);
                EV_INFO << "Dropping packet " << packet->getName() << " from the queue.\n";
                queue.remove(packet);
                dropPacket(packet, QUEUE_OVERFLOW);
            }
        }
        else
            throw cRuntimeError("Queue is overloaded but packet dropper function is not specified");
    }
    updateDisplayString();
    if (collector != nullptr && getNumPackets() != 0)
        collector->handleCanPopPacket(outputGate);

}

Packet *PacketQueue::popPacket(cGate *gate)
{
    if(congestionCheck) congestionCheckandEmitSignal();
    Enter_Method("popPacket");
    auto packet = check_and_cast<Packet *>(queue.front());
    EV_INFO << "Popping packet " << packet->getName() << " from the queue." << endl;
    if (buffer != nullptr) {
        queue.remove(packet);
        buffer->removePacket(packet);
    }
    else
        queue.pop();
    emit(packetPoppedSignal, packet);
    updateDisplayString();
    animateSend(packet, outputGate);
    return packet;
}

void PacketQueue::removePacket(Packet *packet)
{
    Enter_Method("removePacket");
    EV_INFO << "Removing packet " << packet->getName() << " from the queue." << endl;
    if (buffer != nullptr) {
        queue.remove(packet);
        buffer->removePacket(packet);
    }
    else
        queue.remove(packet);
    emit(packetRemovedSignal, packet);
    updateDisplayString();
}

bool PacketQueue::canPushSomePacket(cGate *gate) const
{
    if (packetDropperFunction)
        return true;
    if (getMaxNumPackets() != -1 && getNumPackets() >= getMaxNumPackets())
        return false;
    if (getMaxTotalLength() != b(-1) && getTotalLength() >= getMaxTotalLength())
        return false;
    return true;
}

bool PacketQueue::canPushPacket(Packet *packet, cGate *gate) const
{
    if (packetDropperFunction)
        return true;
    if (getMaxNumPackets() != -1 && getNumPackets() >= getMaxNumPackets())
        return false;
    if (getMaxTotalLength() != b(-1) && getMaxTotalLength() - getTotalLength() < packet->getDataLength())
        return false;
    return true;
}

void PacketQueue::handlePacketRemoved(Packet *packet)
{
    Enter_Method("handlePacketRemoved");
    if (queue.contains(packet)) {
        EV_INFO << "Removing packet " << packet->getName() << " from the queue." << endl;
        queue.remove(packet);
        emit(packetRemovedSignal, packet);
        updateDisplayString();
    }
}

} // namespace queueing
} // namespace inet

