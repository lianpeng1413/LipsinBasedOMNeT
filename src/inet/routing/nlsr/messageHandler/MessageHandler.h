/*
 * MessageHandler.h
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_MESSAGEHANDLER_MESSAGEHANDLER_H_
#define INET_ROUTING_NLSR_MESSAGEHANDLER_MESSAGEHANDLER_H_

#include "inet/common/INETDefs.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/messageHandler/HelloHandler.h"
#include "inet/routing/nlsr/messageHandler/IMessageHandler.h"
#include "inet/routing/nlsr/messageHandler/LSAHandler.h"
#include "inet/routing/nlsr/messageHandler/SyncHandler.h"
#include "inet/networklayer/contract/ndn/iName.h"

namespace inet {
namespace nlsr {

class INET_API MessageHandler : public IMessageHandler
{
  private:
    cSimpleModule *nlsrModule;
    HelloHandler helloHandler;
    LSAHandler lsaHandler;
    SyncHandler syncHandler;
    MacAddress myMacAddress;

  public:
    MessageHandler(Router *containingRouter, cSimpleModule *containingModule);

    void messageReceived(cMessage *message);
    void handleTimer(cMessage *timer);

    void processPacket(Packet *packet, NlsrInterface *unused1 = nullptr, Neighbor *unused2 = nullptr);

    void sendPacket(Packet *packet, iName neighbor, NlsrInterface *outputIf, short ttl = 1);
    void clearTimer(cMessage *timer);
    void startTimer(cMessage *timer, simtime_t delay);
    SyncHandler *getSyncHandler(){ return &syncHandler;}

    void printEvent(const char *eventString, const NlsrInterface *onInterface = nullptr, const Neighbor *forNeighbor = nullptr) const;
    void printHelloInterestPacket(const NlsrHelloInterest *helloPacket, std::string neighbor, int outputIfIndex) const;
    void printHelloDataPacket(const NlsrHelloData *helloPacket, std::string neighbor, int outputIfIndex) const;
    void printSyncInterestPacket(const syncInterest *syncInterestPacket, std::string neighbor, int outputIfIndex) const;
    void printSyncDataPacket(const syncData *syncDataPacket, std::string neighbor, int outputIfIndex) const;
    void printNameLsaInterestPacket(const NameLsaInterest *nameInterestPacket, std::string neighbor, int outputIfIndex) const;
    void printNameLsaDataPacket(const NameDataPacket *nameDataPacket, std::string neighbor, int outputIfIndex) const;
    void printAdjLsaInterestPacket(const AdjLsaInterest *adjInterestPacket, std::string neighbor, int outputIfIndex) const;
    void printAdjLsaDataPacket(const AdjDataPacket *adjDataPacket, std::string neighbor, int outputIfIndex) const;
};

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_MESSAGEHANDLER_MESSAGEHANDLER_H_ */
