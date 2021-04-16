/*
 * LipsinForwarder.h
 *
 *  Created on: Mar 11, 2021
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_LIPSIN_LIPSINFORWARDER_H_
#define INET_NETWORKLAYER_LIPSIN_LIPSINFORWARDER_H_

#include <set>
#include <list>

#include "inet/common/INETDefs.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/contract/INetfilter.h"
#include "inet/networklayer/contract/INetworkProtocol.h"
#include "inet/networklayer/lipsin/LipsinHeader_m.h"
#include "inet/networklayer/lipsin/LipsinLdEntry.h"
#include "inet/networklayer/lipsin/LipsinLdTable.h"
#include "inet/networklayer/lipsin/LipsinNeighborTable.h"
namespace inet {
class INET_API LipsinForwarder : public OperationalBase, public NetfilterBase, public INetworkProtocol,public IProtocolRegistrationListener, public cListener
{
    public:
    /**
     * Represents an LipsinHeader, queued by a Hook
     */
        class QueuedDatagramForHook
        {
          public:
            QueuedDatagramForHook(Packet *packet, IHook::Type hookType) :
                packet(packet), hookType(hookType) {}
            virtual ~QueuedDatagramForHook() {}

            Packet *packet = nullptr;
            const IHook::Type hookType = static_cast<IHook::Type>(-1);
        };
        typedef std::map<int,cPacketQueue> PendingPackets; //need to fix  map indexed with IPv4Address for outbound packets waiting for ARP resolution

    protected:


            cModule *host = nullptr; // for subscribe the link signal
            IInterfaceTable *ift = nullptr;
            LipsinNeighborTable *nbt = nullptr;
            LipsinLdTable *plt = nullptr,*dlt = nullptr,*vlt = nullptr;
            int transportInGateBaseId = -1;

            simtime_t deletePeriod;
            //config maybe useful
            bool limitedBroadcast = false;
            std::string directBroadcastInterfaces = "";

            cPatternMatcher directBroadcastInterfaceMatcher;

            std::set<const Protocol *> upperProtocols;

            //statistics
            int numMulticast = 0;
            int numLocalDeliver = 0;
            int numDropped = 0;
            int numUnroutable = 0;
            int numForwarded = 0;

            typedef std::list<QueuedDatagramForHook> DatagramQueueForHooks;
            DatagramQueueForHooks queuedDatagramsForHooks;

            virtual void subscribe();
            virtual void unsubscribe();
            virtual void handleRegisterService(const Protocol& protocol, cGate *out, ServicePrimitive servicePrimitive) override;
            virtual void handleRegisterProtocol(const Protocol& protocol, cGate *in, ServicePrimitive servicePrimitive) override;

            // utility: show current statistics above the icon
            virtual void refreshDisplay() const override;
            // utility: look up interface from getArrivalGate()
            virtual const InterfaceEntry *getSourceInterface(Packet *packet);
            virtual const InterfaceEntry *getDestInterface(Packet *packet);

            virtual int numInitStages() const override { return NUM_INIT_STAGES; }
            virtual void initialize(int stage) override;
            virtual void handleMessageWhenUp(cMessage *msg) override;
            void handleRequest(Request *request);

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


    protected:
          /**
           * Encapsulate packet coming from higher layers into LipsinHeader, using
           * the given control info. Override if you subclassed controlInfo and/or
           * want to add options etc to the datagram.
           */
            virtual void encapsulate(Packet *packet); //maybe don't need
            /**
             * Handle LipsinHeader messages arriving from lower layer.
             * Just Find downLink and add the link ID into BF
             */
            virtual void handleIncomingDatagram(Packet *packet);

            /**
             * Handle messages (typically packets to be send in Lipsin) from transport
             * Invokes encapsulate(), then routePacket().
             */
            virtual void handlePacketFromHL(Packet *packet);
            virtual void sendPacketToHL(Packet *packet);

            /**
             * Decapsulate packet.
             */
            virtual void decapsulate(Packet *packet);
            /**
             * Send datagram on the given interface.
             */
            virtual void sendDatagramToOutput(Packet *packet,int nic);

            virtual void sendPacketToNIC(Packet *packet);

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

    public:
            LipsinForwarder();
            virtual ~LipsinForwarder();


    protected:
          virtual void start();
          virtual void stop();
          virtual void flush();
};

} /* namespace inet */
#endif /* INET_NETWORKLAYER_LIPSIN_LIPSINFORWARDER_H_ */
