/*
 * ndnFragBuf.cc
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#include <stdlib.h>
#include <string.h>

#include "ndnFragBuf.h"
#include "inet/networklayer/contract/ndn/Interest_m.h"
#include "inet/networklayer/contract/ndn/iData_m.h"

namespace inet{

ndnFragBuf::ndnFragBuf()
{
//    bufs.clear();
}

ndnFragBuf::~ndnFragBuf()
{
    flush();
}

void ndnFragBuf::flush()
{
    for (auto i = bufs.begin(); i != bufs.end(); ++i)
        delete i->second.packet;
    bufs.clear();
}

Packet *ndnFragBuf::addFragment(Packet *packet, simtime_t now) //TODO
{
    auto test = packet->getDataLength().get()/8;
    const auto& DataHead = packet->peekAtFront<iData>(B(128),0);
    auto interest = DataHead->getInterestName();
    auto i = bufs.find(interest);

    DatagramBuffer *curBuf = nullptr;
    if (i == bufs.end()) {
        // this is the first fragment of that datagram, create reassembly buffer for it
        curBuf = &bufs[interest];
        i = bufs.find(interest);
    }
    else {
        // use existing buffer
        curBuf = &(i->second);
    }

    B bytes = DataHead->getTotalLength() - DataHead->getHeaderLength();

    auto hL = B(DataHead->getHeaderLength()).get();
    auto len = bytes.get();
    auto datalen = packet->getDataLength().get() / 8;

    curBuf->buf.replace(B(DataHead->getOffset()), packet->peekDataAt(B(DataHead->getHeaderLength()), bytes));
    if(!DataHead->getMoreFragments()){
        curBuf->buf.setExpectedLength(B(DataHead->getOffset()) + bytes);
    }
    if (DataHead->getOffset() == 0 || curBuf->packet == nullptr) {
        delete curBuf->packet;
        curBuf->packet = packet;
    }
    else {
        delete packet;
    }

    if (curBuf->buf.isComplete())
    {
        std::string pkName(curBuf->packet->getName());
        std::size_t found = pkName.find("-frag-");
        if (found != std::string::npos)
            pkName.resize(found);
        auto hdr = Ptr<iData>(curBuf->packet->peekAtFront<iData>()->dup());
        Packet *pk = curBuf->packet;
        pk->setName(pkName.c_str());
        pk->removeAll();
        const auto& payload = curBuf->buf.getReassembledData();
        hdr->setTotalLength(hdr->getHeaderLength() + payload->getChunkLength());
        hdr->setOffset(0);
        hdr->setMoreFragments(false);
        pk->insertAtFront(hdr);
        pk->insertAtBack(payload);
        bufs.erase(i);
        return pk;
    }
    else
    {
        curBuf->lastupdate = now;
        return nullptr;
    }
}

void ndnFragBuf::purgeStaleFragments(simtime_t lastupdate)
{
    // this method shouldn't be called too often because iteration on
    // an std::map is *very* slow...
    for (auto i = bufs.begin(); i != bufs.end(); ) {
        // if too old, remove it
        DatagramBuffer& buf = i->second;
        if (buf.lastupdate < lastupdate) {

            if (buf.packet != nullptr)

            // delete
            auto oldi = i++;

        }
        else {
            ++i;
        }
    }
}

void ndnFragBuf::clear()
{
    bufs.clear();
}

} // namespace inet


