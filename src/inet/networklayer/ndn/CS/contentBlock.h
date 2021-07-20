/*
 * contentBlock.h
 *
 *  Created on: Oct 1, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDN_CS_CONTENTBLOCK_H_
#define INET_NETWORKLAYER_NDN_CS_CONTENTBLOCK_H_

#include<vector>
#include<list>
#include "inet/common/INETDefs.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/common/packet/Packet.h"

#include "inet/networklayer/contract/ndn/iName.h"
#include "cacheTable.h"
#include "ndnChunk.h"

namespace inet{

class cacheTable;
class ndnChunk;

class INET_API contentBlock : public cObject
{
private:
    // cache table who own this block
    cacheTable* cct = nullptr;
    iName interest;
    unsigned chunksize = 7500;
    unsigned int num=5;
    unsigned int mtu=1500;
    simtime_t lifeTime = 4;  // interest life time
    simtime_t useTime;
    B size; // the block size
    void CaculateSize();

public:
    std::list<Packet *> packets;
    contentBlock(iName interest, unsigned mtu = 1500, simtime_t lifeTime = 4):interest(interest),mtu(mtu), lifeTime(lifeTime + simTime()){};
//    contentBlock() : mtu(1500) {};
    ~contentBlock();

    ndnChunk* createNewChunk();
    void insterPacket(Packet* );
    void removeChunk(ndnChunk* );
    void setCacheTable(cacheTable* table){cct = table;};
    bool checkIntegrity(ndnChunk* );
    bool hasThisPacket(Packet *packet);
    std::list<Packet *> getList() { return packets; }
    unsigned getNum(){return num;}
    B getBlockSize(){return size;}
    std::string str();
    void flush();

    void setUseTime(simtime_t use) { useTime = use; }
    simtime_t getUseTIme() { return useTime;}
    void setLifeTime(simtime_t ttl) { lifeTime = ttl; }
    simtime_t getLifeTime() { return lifeTime; }
};

}

#endif /* INET_NETWORKLAYER_NDN_CS_CONTENTBLOCK_H_ */



