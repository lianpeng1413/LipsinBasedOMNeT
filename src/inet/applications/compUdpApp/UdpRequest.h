/*
 * UdpRequest.h
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_UDPREQUEST_H_
#define INET_APPLICATIONS_COMPUDPAPP_UDPREQUEST_H_

#include <unordered_map>
#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "inet/mobility/base/MobilityBase.h"

namespace inet {

/**
 * packet request client application.
 */
class INET_API UdpRequest : public ApplicationBase, public UdpSocket::ICallback
{
  public:
    struct SimRecorder
    {
        UdpRequest *owner;

        int multiConsumer;

        std::string nodeName;
        std::vector<double> delayArray;
        std::vector<double> puts;

        double tempThput;

        B throughput = B(0);
        int requestSendNum = 0;
        int requestRecvNum = 0;

        int DataSendNum = 0;
        int DataRecvNum =0;
        simtime_t delay = 0;
        simtime_t last = 0;

        void ConsumerPrint(std::ostream &os);

        void ProviderPrint(std::ostream &os);
    };

    enum class SendMode
    {
      EqualInterval = 1,
      UniformDisInterval = 2,
      ExpDisInterval = 3
    };

  protected:

    SimRecorder Recorder;
    // state
    UdpSocket socket;
    cMessage *selfMsg = nullptr;
    cMessage *timer = nullptr;
    double interval;

    std::unordered_map<int, double> delayMap; 

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    virtual void requestStream();
    virtual void receiveStream(Packet *msg);

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
    int helloInterval;
    int seqNum = 0;
    double pktNum;
    std::string path;
    std::string packetName = "";
    UdpRequest() { }
    ~UdpRequest();
    int getHelloInterval(){ return helloInterval;}
//    virtual ~UdpRequest() { cancelAndDelete(selfMsg); }
};

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_UDPREQUEST_H_ */
