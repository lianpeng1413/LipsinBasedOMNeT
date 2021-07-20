/*
 * ndnFlood.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_NDNFLOOD_NDNFLOOD_NDNFLOOD_H_
#define INET_NETWORKLAYER_NDNFLOOD_NDNFLOOD_NDNFLOOD_H_

#include <list>
#include <queue>
#include <map>
#include <set>
#include <fstream>

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/networklayer/contract/ndn/Interest_m.h"
#include "inet/networklayer/contract/ndn/iData_m.h"
#include "inet/networklayer/ndn/FIB/fibBase.h"
#include "inet/networklayer/ndn/FIB/iFib_m.h"
#include "inet/networklayer/ndn/PIT/pitBase.h"
#include "inet/networklayer/ndn/CS/cacheTable.h"
#include "inet/networklayer/ndn/CS/ndnChunk.h"
#include "inet/networklayer/ndn/NFD/ndnFragBuf.h"
#include "inet/common/INETDefs.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/contract/INetworkProtocol.h"
#include "inet/networklayer/contract/INetfilter.h"

namespace inet{

class cacheTable;
class pitBase;
class fibBase;

class INET_API ndnFlood : public OperationalBase, public INetworkProtocol, public NetfilterBase, public IProtocolRegistrationListener, public cListener
{
public:
    struct SimRecorder
    {
        ndnFlood *owner;
        int multiConsumer;
        int index;
        std::map<iName, simtime_t> Delays;
        B throughput = B(0);
        int InterestSendNum = 0;
        int InterestRecvNum = 0;

        int DataSendNum = 0;
        int DataRecvNum =0;
        simtime_t delay = 0;
        void ConsumerPrint(std::ostream &os);
        void ProviderPrint(std::ostream &os);
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
    fibBase *rt = nullptr;  //TODO

    int mtu;
    std::set<const Protocol *> upperProtocols;

    iName nid;
    int hopLimit;
    InterfaceEntry * ie;
    ndnFragBuf* ResemBuffer;

    cMessage* testTimer;
    cMessage* testInterest;
    simtime_t testinterest;

    cMessage* testData;
    simtime_t testdata;

    simtime_t startTime;
    int Cindex = -1;  //TODO not understand
    int Pindex = -1;

    double sendInterval;
    SimRecorder testModule;
    int TC;

    bool flood = true;
    bool unicast;
    double routeLifeTime;
    MacAddress myMacAddress;

protected:
    virtual void
    finish() override;
    virtual void start();
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

    /**
     * called before a packet arriving from the network is routed
     */
    IHook::Result datagramPreRoutingHook(Packet *datagram);

    /**
     * called before a packet arriving from the network is delivered via the network
     */
    IHook::Result datagramForwardHook(Packet *datagram);

    /**
     * called before a packet is delivered via the network
     */
    IHook::Result datagramPostRoutingHook(Packet *datagram);

    /**
     * called before a packet arriving from the network is delivered locally
     */
    IHook::Result datagramLocalInHook(Packet *datagram);

    /**
     * called before a packet arriving locally is delivered
     */
    IHook::Result datagramLocalOutHook(Packet *datagram);

public:
    /**
     * registers a Hook to be executed during datagram processing
     */
    virtual void registerHook(int priority, IHook *hook) override;

    /**
     * unregisters a Hook to be executed during datagram processing
     */
    virtual void unregisterHook(IHook *hook) override;

    /**
     * drop a previously queued datagram
     */
    virtual void dropQueuedDatagram(const Packet *datagram) override;

    /**
     * re-injects a previously queued datagram
     */
    virtual void reinjectQueuedDatagram(const Packet *datagram) override;

    ndnFlood(){}

    ~ndnFlood();

    void handleInterestPacket(Packet* packet);
    void handleDataPacket(Packet* packet);
    shared_ptr<iFib> findRoute(const iName &interest);  //TODO
    void cachePacket(const iName &interest, Packet* packet, iName & originRouter);
    shared_ptr<contentBlock> findContentInCache(const iName &interest);
    void createPIT(const iName& interest, const iName& nid, const MacAddress& mac,simtime_t t, int interfaceId);
    pitBase::EntrysRange findPITentry(const iName &interest);
    void encapsulate(Packet *packet, int type, const iName& interest);
    void encapsulate(Packet *packet, int type, const iName& interest, int port);
    void decapsulate(Packet *packet, const iName& interest);
    void cacheData(const iName &interest, Packet *packet, iName & originRouter);
    void sendDatagramToOutput(Packet *packet, int nic, const MacAddress& mac = MacAddress::BROADCAST_ADDRESS);
    void handlePacketFromHL(Packet *packet);
    void handleIncomingDatagram(Packet *packet);
    InterfaceEntry *chooseInterface(const char* interfaceName);
    const InterfaceEntry *getSourceInterface(Packet *packet);

    void testSend(const iName &interest);
    void sendInterest(const iName &interest, int port);
    void testProvide(const iName &interest, const B& dataSize);
    void record();

    void fragmentAndSend(Packet* packet);
    void fragmentAndStore(Packet* packet, const iName& interest, iName & originRouter);
    const Ptr<inet::Interest> InterestHead(const iName &interest); //TODO
    const Ptr<inet::iData> DataHead(const iName &interest);
    void sendUp(Packet *pkt, SocketDescriptor *sd);
    void handleRequest(Request *request);
    // void handleDelayPkt(Packet *pkt, int seq=0, simtime_t delay=0);

};

}

#endif /* INET_NETWORKLAYER_NDNFLOOD_NDNFLOOD_NDNFLOOD_H_ */
