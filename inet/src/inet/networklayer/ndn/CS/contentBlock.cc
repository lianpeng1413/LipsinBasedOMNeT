/*
 * contentBlock.cc
 *
 *  Created on: Oct 1, 2020
 *      Author: root
 */

#include <sstream>
#include <algorithm>

#include "inet/networklayer/contract/ndn/iData_m.h"
#include "contentBlock.h"

namespace inet
{

ndnChunk *contentBlock::createNewChunk()
{
    ndnChunk *chunk = new ndnChunk(mtu, 0, 5);
    return chunk;
}

void contentBlock::insterPacket(Packet *packet)
{

    packets.push_back(packet);
    num++;
}

void contentBlock::removeChunk(ndnChunk *chunk)
{
}

bool contentBlock::checkIntegrity(ndnChunk *chunk)
{
    return chunk->isIntegrity();
}

std::string contentBlock::str()
{
    std::string result(" ");
    return result;
}

contentBlock::~contentBlock()
{
}

bool contentBlock::hasThisPacket(Packet *packet)
{
    auto function = [packet](Packet *p) -> bool {
        const auto &head1 = p->peekAtFront<iData>();
        const auto &head2 = packet->peekAtFront<iData>();
        if (head1->getOffset() == head2->getOffset() && head1->getTotalLength() == head2->getTotalLength())
            return true;
        else
            return false;
    };

    if (find_if(packets.begin(), packets.end(), function) == packets.end())
        return false;
    else
        return true;
}

void contentBlock::flush()
{
    for_each(packets.begin(), packets.end(), [](Packet* p) {
        Packet *temp = p;
        delete temp;
        p = nullptr;
    });
    packets.clear();
}
} //namespace inet


