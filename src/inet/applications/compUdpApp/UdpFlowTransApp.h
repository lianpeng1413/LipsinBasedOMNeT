/*
 * UdpFlowTransApp.h
 *
 *  Created on: Mar 28, 2021
 *      Author: zeus_yf
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_UDPFLOWTRANSAPP_H_
#define INET_APPLICATIONS_COMPUDPAPP_UDPFLOWTRANSAPP_H_

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet
{
  /**
 * A flow transmission client application.
 *
 * Clients connect to server and get a file.
 */

class INET_API UdpFlowTransApp : public ApplicationBase, public UdpSocket::ICallback
{
public:
    struct SimRecorder
    {
      UdpFlowTransApp *owner;

      std::string nodeName;
      std::vector<double> delayArray;

      B throughput = B(0);
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
    cMessage *timer = nullptr;
    cMessage *timeout = nullptr;
    bool greedy;

    uint32_t NowOffset;
    B pktSize = B(0);
    int seq = 0;
    double interval = 0.05;
    double limit = 0.25;

    std::set<int> recieveSET;
    std::map<int, uint32_t> seqToOffset;

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    virtual void requestFile();
    virtual void receiveFile(Packet *msg);

    void bindSocket();
    void moveOn();

    void sendReq();

    // ApplicationBase:
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    virtual void socketClosed(UdpSocket *socket) override;

  public:
    double startTime;
    double sendInterval;
    int flowNum;    // the number of flows.
    std::string path;
    UdpFlowTransApp() {}
    virtual ~UdpFlowTransApp() { cancelAndDelete(selfMsg); }
  };

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_UDPFLOWTRANSAPP_H_ */
