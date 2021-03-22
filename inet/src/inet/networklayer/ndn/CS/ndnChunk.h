/*
 * ndnChunk.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDN_CS_NDNCHUNK_H_
#define INET_NETWORKLAYER_NDN_CS_NDNCHUNK_H_

#include <vector>
#include <list>

#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "cacheTable.h"

namespace inet{

class INET_API ndnChunk
{
private:
    unsigned mtu = 2304;
    unsigned index;
    // chunk size, it will update, after inserting packet
    B size;

    unsigned packet_num;

    std::vector<Packet*> packets;
    void caculateSize();

public:
    ndnChunk(unsigned m, unsigned index, unsigned num):mtu(m),index(index),packet_num(num)
    {
        for(unsigned int i = 0; i < packet_num; i++)
        {
            packets.push_back(nullptr);
        }
    }

    ~ndnChunk(){
        for(auto iter:packets)
        {
            delete iter;
        }
    }
    bool isIntegrity();
    void setIndex(unsigned i);
    unsigned getIndex();
    void fillPacket(Packet*,int);
    B getSize();
    Packet* getPacket(unsigned i);

    const std::vector<Packet*> getPackets(){return packets;}
};
}

#endif /* INET_NETWORKLAYER_NDN_CS_NDNCHUNK_H_ */
