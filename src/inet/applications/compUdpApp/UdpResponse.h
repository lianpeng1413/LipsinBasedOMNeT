/*
 * UdpResponse.h
 *
 *  Created on: May 20, 2020
 *      Author: hiro
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_UDPRESPONSE_H_
#define INET_APPLICATIONS_COMPUDPAPP_UDPRESPONSE_H_

#include <map>

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet {

/**
 * Generate packet to clients.
 *
 * Cooperates with UdpRequst client.
 */
class INET_API UdpResponse : public ApplicationBase, public UdpSocket::ICallback
{
public:

protected:
    int rngNum;

    UdpSocket socket;

    // parameters
    int localPort = -1;
    cPar *sendInterval = nullptr;
    cPar *packetLen = nullptr;
    std::string packetName = "";
    // statistics
    unsigned long numPkSent = 0;    // total number of packets sent
    static simsignal_t reqStreamBytesSignal;    // length of streams served

    virtual void processStreamRequest(Packet *msg);
    virtual void sendReply(cMessage *timer, simtime_t timeStamp, int seq);

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    virtual void clearStreams();

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    virtual void socketClosed(UdpSocket *socket) override;

public:
    UdpResponse() {}
    virtual ~UdpResponse();
};

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_UDPRESPONSE_H_ */
