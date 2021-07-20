/*
 * fileTransProvider.h
 *
 */

#ifndef INET_APPLICATIONS_ICNAPP_FILETRANSPROVIDER_H_
#define INET_APPLICATIONS_ICNAPP_FILETRANSPROVIDER_H_

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

class INET_API fileTransProvider : public ApplicationBase, public ndnSocket::ICallback
{
private:
    iName nid;
    int pktLen = 0;
    const char* nodeName;
    std::string pPrefix;
    int localPort;
    ndnSocket *currentSocket = nullptr;
    cMessage *start = nullptr;

public:
    simtime_t startTime;
    long int sFragNum = 0;
    long int content = 0;
    double fileTransDelay;
    double fileSize;
    cPar *filesSize = nullptr;

    fileTransProvider(){};
    ~fileTransProvider(){};

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

#endif /* INET_APPLICATIONS_ICNAPP_FILETRANSPROVIDER_H_ */
