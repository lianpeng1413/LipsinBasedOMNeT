/*
 * fileProvider.h
 *
 *  Created on: May 20, 2020
 *      Author: hiro
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_FILEPROVIDER_H_
#define INET_APPLICATIONS_COMPUDPAPP_FILEPROVIDER_H_

#include <map>

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet {

/**
 * file transfer to clients.
 */
class INET_API UdpFileProvider : public ApplicationBase, public UdpSocket::ICallback
{
public:
    struct fileFragmentsData
    {
        cMessage *timer = nullptr;    // self timer msg
        L3Address clientAddr;    // client address
        int clientPort = -1;    // client UDP port
        long int fragment = 0;    // fragment
    };

protected:
    int rngNum;
    UdpSocket socket;

    // state
    typedef std::map<long int, fileFragmentsData> fileFragmentsMap;
    fileFragmentsMap fileFragments;
    std::set<L3Address> clientAddrs;

    // parameters
    int localPort = -1;
    cPar *sendInterval = nullptr;
    double sendIntervals = 0;
    cPar *packetLen = nullptr;
    double fileSize;
    cPar *filesSize = nullptr;
    long int sFragNum= 0;

    // statistics
    long int numFiles = 0;    // number of file served
    unsigned long numPkSent = 0;    // total number of packets sent

    virtual void processFileRequest(Packet *msg);
    void generateFileSendSet(Packet *msg);
    virtual void sendFileData(double seq, L3Address clientAddr, int clientPort);
    void sendFileFragment(cMessage *msg);
    void removeFragment(long int timerID);

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void clearFiles();

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    virtual void socketClosed(UdpSocket *socket) override;

public:
    UdpFileProvider() {}
    virtual ~UdpFileProvider();
};

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_FILEPROVIDER_H_ */
