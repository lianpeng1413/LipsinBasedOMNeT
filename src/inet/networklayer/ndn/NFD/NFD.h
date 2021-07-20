/*
 * NFD.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDN_NFD_NFD_H_
#define INET_NETWORKLAYER_NDN_NFD_NFD_H_

#include <list>
#include <queue>
#include <map>
#include <set>
#include <fstream>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/networklayer/contract/ndn/Interest_m.h"
#include "inet/networklayer/contract/ndn/iData_m.h"
#include "inet/networklayer/ndn/CS/cacheTable.h"
#include "inet/networklayer/ndn/CS/ndnChunk.h"
#include "inet/routing/nlsr/router/route/fib.h"
#include "inet/networklayer/ndn/PIT/pitBase.h"
#include "inet/common/INETDefs.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/contract/INetworkProtocol.h"
#include "inet/networklayer/contract/INetfilter.h"
#include "ndnFragBuf.h"
#include "inet/routing/nlsr/router/route/fibEntry_m.h"

namespace inet{

class cacheTable;
class pitBase;
//class inet::nlsr::Fib;

class INET_API NFD : public OperationalBase, public INetworkProtocol, public IProtocolRegistrationListener, public cListener
{
public:
    //Simulation results recorder
    struct SimRecorder
    {
        NFD *owner;
        int multiConsumer;
        int index;
        std::string nodeName;
        std::map<iName, simtime_t> Delays;
        std::vector<double> delayArrary;
        std::vector<double> puts;

        std::map<double, std::map<double, double>> avgThoughputT;
        std::map<double, double> temp;
        double tempThput;

        B goodThroughput = B(0);
        B totalThroughput = B(0);

        double InterestSendNum = 0;
        double InterestRecvNum = 0;

        double DataSendNum = 0;
        double DataRecvNum =0;
        simtime_t delay = 0;

        void ConsumerPrint(std::ostream &os);
        void ProviderPrint(std::ostream &os);
        void avtThroughputPrint(std::ostream &os);
    };

    struct SocketDescriptor
    {
        int socketId = -1;
        int protocolId = -1;
        iName nid;
        int localPort;

        SocketDescriptor(int socketId, int protocolId, const iName& nid ,int port)
        : socketId(socketId), protocolId(protocolId), nid(nid),localPort(port) {}
    };

    class interestIdentifier
    {
    public:
        iName interest;
        iName requester;

        interestIdentifier(const iName& interest, const iName& nid) : interest(interest), requester(nid){}
        bool operator == (const interestIdentifier& other) const {
            return interest == other.interest && requester == other.requester;
        }
    };

    class interestIdentifierComparor
    {
    public:
        bool operator ()(const interestIdentifier& lhs, const interestIdentifier& rhs)
        {
            if (lhs.interest == rhs.interest)
                return lhs.requester < rhs.requester;
            else return lhs.interest < rhs.interest;
        }
    };

    enum class SendMode
    {
        EqualInterval = 1,
        UniformDisInterval = 2,
        ExpDisInterval = 3
    };

private:
    friend class SimRecorder;
    simtime_t firstPacket;
    int nodeIndex;
    const char* nodeName;
    std::map<interestIdentifier, simtime_t, interestIdentifierComparor> interestTable;
    std::map<double, SocketDescriptor *> socketIdToSocketDescriptor;
    std::map<double, SocketDescriptor *> socketsByPortMap;
    std::map<iName, double> iNametoSockets;

    IInterfaceTable *ift = nullptr;
    cacheTable *ct = nullptr;
    pitBase *pit = nullptr;
    nlsr::Fib *rt = nullptr;  //TODO
    nlsr::Router *childRouter;

    std::map<iName, int> receiveMap;
    int mtu;
    std::set<const Protocol *> upperProtocols;

    iName nid;
    int hopLimit;
    InterfaceEntry * ie;
    ndnFragBuf* ResemBuffer;

    simtime_t startTime;
    std::string CnodeName;
    std::string PnodeName;
    std::string RSpath;

    double sendInterval;
    SimRecorder testModule;
    int TC;

    bool flood = true;
    bool unicast;
    double routeLifeTime;
    MacAddress myMacAddress;

    simtime_t timeOut;
    cMessage *avgThroughputTime;  // recorder average throughput and delay every 10 seconds
    double maxInterestDelay = 0;
    std::map<interestIdentifier, simtime_t, interestIdentifierComparor> InterestTable;
    int syncInterval;

protected:
    virtual void finish() override;
    /**
     * IProtocolRegistrationListener methods
     */
    virtual void handleRegisterService(const Protocol& protocol, cGate *out, ServicePrimitive servicePrimitive) override;
    virtual void handleRegisterProtocol(const Protocol& protocol, cGate *in, ServicePrimitive servicePrimitive) override;
    /**
     * OperationalBase methods
     */
    virtual void refreshDisplay() const override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    /**
     * ILifecycle methods
     */
    virtual bool isInitializeStage(int stage) override { return stage == INITSTAGE_NETWORK_LAYER; }
    virtual bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_NETWORK_LAYER; }
    virtual bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_NETWORK_LAYER; }
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    /// cListener method
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

public:
    NFD(){}
    ~NFD();

    void createPIT(const iName& interest, const iName& nid, const MacAddress& mac,simtime_t t, int interfaceId);
    void cacheDataFromHL(const iName &interest, Packet* packet, iName & originRouter);
    std::shared_ptr<contentBlock> cacheDataFromLL(const iName &interest, Packet *packet, iName & originRouter);
    InterfaceEntry *chooseInterface(const char* interfaceName);

    void encapsulate(Packet *packet, int type, const iName& interest);
    void encapsulate(Packet *packet, int type, const iName& interest, int port);
    void decapsulate(Packet *packet, const iName& interest);
    const Ptr<inet::iData> DataHead(const iName &interest);

    shared_ptr<inet::nlsr::FibEntry> findRoute(const iName &interest);
    shared_ptr<contentBlock> findContentInCache(const iName &interest);
    pitBase::EntrysRange findPITentry(const iName &interest);
//    void fragmentAndStore(Packet* packet, const iName& interest, iName & originRouter);

    const InterfaceEntry *getSourceInterface(Packet *packet);
    int getSyncInterval() {return syncInterval;}
    double getSendInterval() {return sendInterval;}
    void handleIncomingDatagram(Packet *packet);
    void handleInterestPacket(Packet* packet);
    void handleDataPacket(Packet* packet);
    void handleRequest(Request *request);  //process upper layer request
    const Ptr<inet::Interest> InterestHead(const iName &interest);

    void record();
    void sendDatagramToOutput(Packet *packet, int nic, const MacAddress& mac = MacAddress::BROADCAST_ADDRESS);
    void sendInterest(const iName &interest, int port);
    void sendUp(Packet *pkt, SocketDescriptor *sd, const iName &interest, double port);
};

}

#endif /* INET_NETWORKLAYER_NDN_NFD_NFD_H_ */
