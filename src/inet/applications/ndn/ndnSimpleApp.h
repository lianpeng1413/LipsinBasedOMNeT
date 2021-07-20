/*
 * ndnSimpleApp.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_APPLICATIONS_NDN_NDNSIMPLEAPP_H_
#define INET_APPLICATIONS_NDN_NDNSIMPLEAPP_H_

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
class INET_API ndnSimpleApp : public ApplicationBase, public ndnSocket::ICallback
{
    public:
        struct SimRecorder
        {
            ndnSimpleApp * owner;
            int multiConsumer;
            std::string cPrefix;

            char nodeName;
            std::string nodeNameOwn;

            B throughput = B(0);
            B totalThroughput = B(0);

            double InterestSendNum = 0;
            double  InterestRecvNum = 0;

            double DataSendNum = 0;
            double DataRecvNum =0;
            simtime_t delay = 0;
            std::map<iName, simtime_t> Delays;
            std::vector<double> delayArrary;
            std::vector<double> puts;

            void consumerPrint(std::ostream &os);
            void providerPrint(std::ostream &os);
        };

    private:
        iName nid;
        double requestNum;
        int rngNum= 1;
        std::string cPrefix;

        long localPort;
        simtime_t stopTime;
        long long content = 0;

        ndnSocket *currentSocket = nullptr;
        cMessage *timer = nullptr;    // to schedule the next Ping request
        cMessage *start = nullptr;
        SimRecorder Recorder;
        std::string path;

    public:
        simtime_t startTime;
        double sendInterval;

        ndnSimpleApp(){};
        ~ndnSimpleApp();

        virtual void initialize(int stage) override;
        virtual int numInitStages() const override { return NUM_INIT_STAGES; }
        virtual void handleMessageWhenUp(cMessage *msg) override;
        virtual void handleSelfMessage(cMessage *msg);
        virtual void finish() override;
        virtual void refreshDisplay() const override;

        void sendRequest(const iName &iName);

        // Lifecycle methods
        virtual void handleStartOperation(LifecycleOperation *operation) override;
        virtual void handleStopOperation(LifecycleOperation *operation) override;
        virtual void handleCrashOperation(LifecycleOperation *operation) override;

        //INetworkSocket::ICallback:
        virtual void socketDataArrived(ndnSocket *socket, Packet *packet) override;
        virtual void socketClosed(ndnSocket *socket) override;
};
} // namespace inet


#endif /* INET_APPLICATIONS_NDN_NDNSIMPLEAPP_H_ */
