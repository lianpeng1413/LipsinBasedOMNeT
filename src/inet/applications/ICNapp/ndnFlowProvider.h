/*
 * ndnFlowProvider.h
 *
 *  Created on: Mar 28, 2021
 *      Author: zeus_yf
 */

#ifndef INET_APPLICATIONS_ICNAPP_NDNFLOWPROVIDER_H_
#define INET_APPLICATIONS_ICNAPP_NDNFLOWPROVIDER_H_

#include "inet/common/INETDefs.h"
#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/Protocol.h"
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/socket/SocketMap.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/contract/INetworkSocket.h"
#include "inet/networklayer/contract/ndn/ndnSocket.h"
#include "inet/networklayer/contract/ndn/iName.h"


namespace inet
{
class INET_API ndnFlowProvider : public ApplicationBase, public ndnSocket::ICallback
{
public:
    struct SimRecorder
    {
        ndnFlowProvider * owner;
        int multiConsumer;

        int index;
        char nodeName;
        std::map<iName, simtime_t> Delays;
        std::vector<double> delayArray;

        B throughput = B(0);
        int InterestSendNum = 0;
        int requestRecvNum = 0;

        int DataSendNum = 0;
        int DataRecvNum =0;
        simtime_t delay = 0;

        void ConsumerPrint(std::ostream &os);
        void ProviderPrint(std::ostream &os);
    };

private:
    iName nid;
    int destIndex;
    int requestNum  = 0;
    int rngNum;
    std::string cPrefix;
    int localPort;

    simtime_t stopTime;
    long long content = 0;

    simtime_t limit = 0.5;
    simtime_t retransTimer = 0.1;

    ndnSocket *currentSocket = nullptr;
    int pid = 0;
    cMessage *timeout = nullptr;    // to schedule the next Ping request
    cMessage *start = nullptr;
    cMessage *reTimer = nullptr;
    SimRecorder Recorder;

    std::string path;

public:
    friend class SimRecorder;

    simtime_t startTime;
    double sendInterval;

    ndnFlowProvider(){};
    ~ndnFlowProvider(){};
    int getPid() const {return pid;}

    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void handleSelfMessage(cMessage *msg);
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    void sendRequest(const iName &interestName);

    // Lifecycle methods
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    //INetworkSocket::ICallback:
    virtual void socketDataArrived(ndnSocket *socket, Packet *packet) override;
    virtual void socketClosed(ndnSocket *socket) override;

};
} // namespace inet

#endif /* INET_APPLICATIONS_ICNAPP_NDNFLOWPROVIDER_H_ */
