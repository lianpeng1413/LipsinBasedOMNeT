/*
 * fileTransApp.h
 *
 *  Created on: May 20, 2020
 *      Author: hiro
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_FILETRANSAPP_H_
#define INET_APPLICATIONS_COMPUDPAPP_FILETRANSAPP_H_

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet
{
  /**
 * A file client application.
 */
class INET_API UdpFileTransApp : public ApplicationBase, public UdpSocket::ICallback
{
public:
    struct SimRecorder
    {
      UdpFileTransApp *owner;

      int multiConsumer;

      std::string nodeName;
      std::vector<double> delayArray;

      int requestSendNum = 0;
      int requestRecvNum = 0;

      int DataSendNum = 0;
      int DataRecvNum = 0;
      simtime_t delay = 0;
      simtime_t last = 0;

      void ConsumerPrint(std::ostream &os);

      void ProviderPrint(std::ostream &os);
    };

  protected:
    SimRecorder Recorder;
    // state
    UdpSocket socket;
    cMessage *selfMsg = nullptr;
    cMessage *timeout = nullptr;
    long int sFragNum = 0;
    long int seq = 0;
    double limit = 0.1;
    int helloInterval;

    std::vector<long int> dataFram;
    std::set<long int> recieveSET;

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    virtual void receiveFile(Packet *msg);
    void bindSocket();

    // ApplicationBase:
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    virtual void socketClosed(UdpSocket *socket) override;

  public:
    double startTime;
    std::string path;
    double fileSize;
    cPar *filesSize = nullptr;

    double fileTransDelay = 0;
    long unsigned reSendNum = 0;
    UdpFileTransApp() {}
    virtual ~UdpFileTransApp() { cancelAndDelete(selfMsg); }
    int getHelloInterval(){ return helloInterval;}
    virtual void requestFile(double seqNo);
  };

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_FILETRANSAPP_H_ */
