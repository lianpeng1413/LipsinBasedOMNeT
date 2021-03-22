/*
 * ndnFragBuf.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDN_NFD_NDNFRAGBUF_H_
#define INET_NETWORKLAYER_NDN_NFD_NDNFRAGBUF_H_

#include <map>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/networklayer/contract/ndn/iData_m.h"
#include "inet/networklayer/contract/ndn/Interest_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/ReassemblyBuffer.h"

namespace inet{

class INET_API ndnFragBuf
{
protected:
    struct DatagramBuffer
    {
        ReassemblyBuffer buf;    // reassembly buffer
        Packet *packet = nullptr;          // the packet
        simtime_t lastupdate;    // last time a new fragment arrived
    };

    typedef std::map<iName,DatagramBuffer> Buffers;
    Buffers bufs;

public:
    ndnFragBuf();
    ~ndnFragBuf();
    Packet *addFragment(Packet *packet, simtime_t now);
    void purgeStaleFragments(simtime_t lastupdate);
    void flush();
    void clear();
};
}

#endif /* INET_NETWORKLAYER_NDN_NFD_NDNFRAGBUF_H_ */
