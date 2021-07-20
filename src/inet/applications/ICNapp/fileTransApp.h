/*
 * fileTransApp.h
 *
 */

#ifndef INET_APPLICATIONS_ICNAPP_FILETRANSAPP_H_
#define INET_APPLICATIONS_ICNAPP_FILETRANSAPP_H_

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
class INET_API fileTransApp : public ApplicationBase, public ndnSocket::ICallback
{
public:
    struct SimRecorder
    {
        fileTransApp * owner;
        int multiConsumer;

        std::string nodeName;
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
    std::string destNode;
    long requestNum = 0;
    long resendNum = 0;
    int rngNum = 0;
    std::string cPrefix;
    int localPort;

    cMessage *timer = nullptr;
    long long content = 0;
    double sendInterval;
    double limit = 0.5;

    ndnSocket *currentSocket = nullptr;
    cMessage *timeout = nullptr;    // to schedule the next fragment request
    cMessage *start = nullptr;
    SimRecorder Recorder;
    std::string path;

public:
    friend class SimRecorder;

    double startTime;
    double fileTransDelay;
    double fileSize;
    cPar *filesSize = nullptr;
    long int sFragNum = 0;
    long int seq = 0;
    std::vector<long int> dataFram;
    std::set<long int> recieveSET;
    int syncInterval;

    fileTransApp(){};
    ~fileTransApp(){};

    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void handleSelfMessage(cMessage *msg);
    virtual void finish() override;
    virtual void refreshDisplay() const override;
    int getSyncInterval(){ return syncInterval;}
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

#endif /* INET_APPLICATIONS_ICNAPP_FILETRANSAPP_H_ */
