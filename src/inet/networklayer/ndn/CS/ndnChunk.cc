/*
 * ndnChunk.cc
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#include "ndnChunk.h"
#include "inet/networklayer/contract/ndn/iData_m.h"

namespace inet{

void ndnChunk::setIndex(unsigned i)
{
    index = i;
}

unsigned ndnChunk::getIndex()
{
    return index;
}

void ndnChunk::fillPacket(Packet* packet, int i)
{
    packets[i] = packet->dup();
}

B ndnChunk::getSize()
{
    return size;
}

Packet* ndnChunk::getPacket(unsigned i)
{
    Packet* packet = new Packet(*packets[i]);
    return packet;
}

bool ndnChunk::isIntegrity()
{
    for(auto iter = packets.begin(); iter !=packets.end(); iter++)
    {
        if((*iter)->getByteLength() == 0)
            return false;
    }
    return true;
}

}


