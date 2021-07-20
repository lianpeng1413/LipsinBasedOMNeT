/*
 * ndnSimpleProvider.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_APPLICATIONS_NDN_NDNSIMPLEPROVIDER_H_
#define INET_APPLICATIONS_NDN_NDNSIMPLEPROVIDER_H_

#include <string>
#include <math.h>
#include <vector>
#include <string.h>
#include <cstring>

#include "inet/networklayer/contract/ndn/ndnSocket.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/common/INETDefs.h"
#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/Protocol.h"
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/socket/SocketMap.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/contract/INetworkSocket.h"

namespace inet
{

class INET_API ndnSimpleProvider : public ApplicationBase, public ndnSocket::ICallback
{
    private:
        iName nid;
        int pktLen;
        double pktNum;
        double pktNum2;
        const char* nodeName;
        std::string pPrefix;

        int localPort;
        simtime_t stopTime;
        ndnSocket *currentSocket = nullptr;

        cMessage *start = nullptr;
        long long content = 0;

        simtime_t timeOut;
        cMessage *regenerateEvent;  // register name event

    public:
        simtime_t startTime;

        ndnSimpleProvider(){};
        ~ndnSimpleProvider();

        virtual void initialize(int stage) override;
        virtual int numInitStages() const override { return NUM_INIT_STAGES; }
        virtual void handleMessageWhenUp(cMessage *msg) override;
        virtual void handleSelfMessage(cMessage *msg);
        virtual void finish() override;
        virtual void refreshDisplay() const override;
        void generateAndCacheData(const iName &interest);

        // Lifecycle methods
        virtual void handleStartOperation(LifecycleOperation *operation) override;
        virtual void handleStopOperation(LifecycleOperation *operation) override;
        virtual void handleCrashOperation(LifecycleOperation *operation) override;

        //INetworkSocket::ICallback:
        virtual void socketDataArrived(ndnSocket *socket, Packet *packet) override;
        virtual void socketClosed(ndnSocket *socket) override;
};
} // namespace inet

#endif /* INET_APPLICATIONS_NDN_NDNSIMPLEPROVIDER_H_ */
