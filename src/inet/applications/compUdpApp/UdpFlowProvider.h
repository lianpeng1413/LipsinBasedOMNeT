/*
 * UdpFlowProvider.h
 *
 *  Created on: Mar 28, 2021
 *      Author: zeus_yf
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_UDPFLOWPROVIDER_H_
#define INET_APPLICATIONS_COMPUDPAPP_UDPFLOWPROVIDER_H_

#include <map>

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet {

class INET_API UdpFlowProvider : public ApplicationBase, public UdpSocket::ICallback
{
public:

protected:
    int rngNum;

    UdpSocket socket;

    // parameters
    int localPort = -1;
    cPar *sendInterval = nullptr;
    cPar *packetLen = nullptr;
    cPar *videoSize = nullptr;
    uint32_t highBit;
    int pktNum;

    // statistics
    unsigned int numStreams = 0;    // number of video streams served
    unsigned long numPkSent = 0;    // total number of packets sent

    virtual void processStreamRequest(Packet *msg);
    virtual void sendFileData(uint32_t offset, int seq, L3Address clientAddr, int clientPort);

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
    UdpFlowProvider() {}
    virtual ~UdpFlowProvider();
};

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_UDPFLOWPROVIDER_H_ */
