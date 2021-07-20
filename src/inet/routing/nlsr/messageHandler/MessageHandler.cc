/*
 * MessageHandler.cc
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {

namespace nlsr {

MessageHandler::MessageHandler(Router *containingRouter, cSimpleModule *containingModule) :
    IMessageHandler(containingRouter),
    nlsrModule(containingModule),
    helloHandler(containingRouter),
    lsaHandler(containingRouter),
    syncHandler(containingRouter)
{
}

void MessageHandler::messageReceived(cMessage *message)
{
    if (message->isSelfMessage()) {
        handleTimer(message);
    }
    else {
        Packet *pk = check_and_cast<Packet *>(message);
        auto protocol = pk->getTag<PacketProtocolTag>()->getProtocol();
        if (protocol == &Protocol::nlsr) {
            EV_INFO << "Receive a NLSR packet.\n";
            processPacket(pk);
        }
    }
}

void MessageHandler::handleTimer(cMessage *timer)
{
    switch (timer->getKind()) {
        case INTERFACE_HELLO_TIMER: {
            NlsrInterface *intf;
            if (!(intf = reinterpret_cast<NlsrInterface *>(timer->getContextPointer()))) {
                // should not reach this point
                EV_INFO << "Discarding invalid InterfaceHelloTimer.\n";
                delete timer;
            }
            else {
                printEvent("Hello Timer expired", intf);
                intf->processEvent(NlsrInterface::HELLO_TIMER);
            }
        }
        break;

        case NEIGHBOR_INACTIVITY_TIMER: {
            Neighbor *neighbor;
            if (!(neighbor = reinterpret_cast<Neighbor *>(timer->getContextPointer()))) {
                // should not reach this point
                EV_INFO << "Discarding invalid NeighborInactivityTimer.\n";
                delete timer;
            }
            else {
                printEvent("Inactivity Timer expired", neighbor->getInterface(), neighbor);
                neighbor->processEvent(Neighbor::INACTIVITY_TIMER);
            }
        }
        break;

        case SYNC_START_TIMER: {
            Neighbor *neighbor;
            if (!(neighbor = reinterpret_cast<Neighbor *>(timer->getContextPointer()))) {
                // should not reach this point
                EV_INFO << "Discarding invalid SYNC Timer.\n";
                delete timer;
            }
            else {
                printEvent("sync Timer expired", neighbor->getInterface(), neighbor);
                neighbor->processEvent(Neighbor::SYNC_TIMER);
            }
        }
        break;

        case DATABASE_AGE_TIMER: {
            printEvent("Aging the database");
            router->ageDatabase();
        }
        break;

        default:
            break;
    }
}

void MessageHandler::processPacket(Packet *pk, NlsrInterface *unused1, Neighbor *unused2)
{
    const auto& packet = pk->peekAtFront<NlsrPacket>();
    EV_INFO << "Received packet: (" << packet.get()->getClassName() << ")" << pk->getName() << "\n";

    auto macInfo = pk->getTag<MacAddressInd>();
    auto neighborMac = macInfo->getSrcAddress();

    // packet version must be NLSR version 2
    if (packet->getVersion() == 2) {
        int interfaceId = pk->getTag<InterfaceInd>()->getInterfaceId();
        NlsrArea *area = router->getAreaByID(0);
        NlsrPacketType packetType = static_cast<NlsrPacketType>(packet->getType());
        Neighbor *neighbor = nullptr;
        NlsrInterface *intf = area->getInterface(interfaceId);
        intf->setNeighborMac(neighborMac);

        //Get neighbor name from packet name.
        iName neighborName;
        std::string name;
        name += packet->getInterestName().getTail();
        neighborName.set(name);
        neighbor = intf->getNeighborByName(neighborName);
//        std::cout << this->router->getRouterID().str() << ", neighbor: " << neighborName.str() << neighbor << ", at:" << simTime() << endl;

        switch (packetType) {
        case HELLO_INTEREST:
            helloHandler.processInterestPacket(pk, intf, unused2);
            break;

        case HELLO_DATA:
            helloHandler.processDataPacket(pk, intf);
            break;

        case SYNC_INTEREST:
        case SYNC_DATA:{
            syncHandler.processPacket(pk, intf, neighbor);
        }
            break;

        case ADJ_LSA_INTEREST:
        case ADJ_LSA_DATA:
        case NAME_LSA_INTEREST:
        case NAME_LSA_DATA:{
            lsaHandler.processPacket(pk, intf, neighbor);
        }
            break;

        default:
            break;
        }
    }
    delete pk;
}

// send packet to linklayer, TODO need to get next router MAC
void MessageHandler::sendPacket(Packet *packet, iName destination, NlsrInterface *outputIf, short ttl)
{
    if(outputIf->getMode() == NlsrInterface::NO_NLSR) {
        delete packet;
        throw cRuntimeError("Interface '%u' is in NoNLSR mode and cannot send out NLSR messages", outputIf->getIfIndex());
    }
    else if(outputIf->getMode() == NlsrInterface::PASSIVE) {
        delete packet;
        return;
    }

    packet->removeTagIfPresent<MacAddressReq>();
    auto macAddrReq = packet->addTag<MacAddressReq>();
    macAddrReq->setSrcAddress(myMacAddress);
    macAddrReq->setDestAddress(outputIf->getNeighborMac());

    int outputIfIndex = outputIf->getIfIndex();
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::nlsr);
    packet->addTagIfAbsent<DispatchProtocolInd>()->setProtocol(&Protocol::nlsr);

    const auto& nlsrPacket = packet->peekAtFront<NlsrPacket>();

    switch (nlsrPacket->getType()) {
        case HELLO_INTEREST: {
            packet->setName("Hello interest");

            const auto& helloInterest = packet->peekAtFront<NlsrHelloInterest>();
            printHelloInterestPacket(helloInterest.get(), destination.str(), outputIfIndex);
        }
        break;

        case HELLO_DATA: {
            packet->setName("Hello data");

            const auto& helloData = packet->peekAtFront<NlsrHelloData>();
            printHelloDataPacket(helloData.get(), destination.str(), outputIfIndex);
        }
        break;

        case SYNC_INTEREST: {
            packet->setName("Sync interest");

            const auto& syncInterestPacket = packet->peekAtFront<syncInterest>();
            printSyncInterestPacket(syncInterestPacket.get(), destination.str(), outputIfIndex);
        }
        break;

        case SYNC_DATA: {
            packet->setName("Sync data");

            const auto& syncDataPacket = packet->peekAtFront<syncData>();
            printSyncDataPacket(syncDataPacket.get(), destination.str(), outputIfIndex);
        }
        break;

        case NAME_LSA_INTEREST: {
            packet->setName("NameLSA interest");

            const auto& nameLsaInterest = packet->peekAtFront<NameLsaInterest>();
            printNameLsaInterestPacket(nameLsaInterest.get(), destination.str(), outputIfIndex);
        }
        break;

        case NAME_LSA_DATA: {
            packet->setName("NameLSA data");

            const auto& nameLsaData = packet->peekAtFront<NameDataPacket>();
            printNameLsaDataPacket(nameLsaData.get(), destination.str(), outputIfIndex);
        }
        break;

        case ADJ_LSA_INTEREST: {
            packet->setName("AdjLSA interest");

            const auto& adjLsaInterest = packet->peekAtFront<AdjLsaInterest>();
            printAdjLsaInterestPacket(adjLsaInterest.get(), destination.str(), outputIfIndex);
        }
        break;

        case ADJ_LSA_DATA: {
            packet->setName("AdjLSA data");

            const auto& adjLsaData = packet->peekAtFront<AdjDataPacket>();
            printAdjLsaDataPacket(adjLsaData.get(), destination.str(), outputIfIndex);
        }
        break;

        default:
            break;
    }

    if (destination != iName::NLSR_ROUTERS_MCAST ) {
        int interfaceNum = router->getNumInterface();
        for(int i = 0; i < interfaceNum;i++)
        {
            const InterfaceEntry *outIE = router->getInterface(i);
            if((outIE->getInterfaceId() == outputIf->getIfIndex()) && outIE->isUp()){ //check interface is up or not.
                packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(outputIfIndex);
                nlsrModule->send(packet->dup(), "ifOut");
           }
        }
    }

    else{ //Broadcast.
        int interfaceNum = router->getNumInterface();
        for(int i = 0; i < interfaceNum;i++)
        {
            const InterfaceEntry *destIE = router->getInterface(i);
            if(!destIE->isLoopback() && destIE->isUp())
            {
                packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(destIE->getInterfaceId());
                nlsrModule->send(packet->dup(), "ifOut");
            }
        }
    }
}

void MessageHandler::clearTimer(cMessage *timer)
{
    nlsrModule->cancelEvent(timer);
}

void MessageHandler::startTimer(cMessage *timer, simtime_t delay)
{
    nlsrModule->cancelEvent(timer);
    nlsrModule->scheduleAt(simTime() + delay, timer);
}

void MessageHandler::printEvent(const char *eventString, const NlsrInterface *onInterface, const Neighbor *forNeighbor    /*= nullptr*/) const
{
    EV_DETAIL << eventString;
    if ((onInterface != nullptr) || (forNeighbor != nullptr)) {
        EV_DETAIL << ": ";
    }
    if (forNeighbor != nullptr) { //todo
        EV_DETAIL << "neighbor["
                  << forNeighbor->getNeighborName()
                  << "] (state: "
                  << forNeighbor->getStateString(forNeighbor->getState())
                  << "); ";
    }
    if (onInterface != nullptr) {
        EV_DETAIL << "interface["
                  << static_cast<short>(onInterface->getIfIndex())
                  << "] ";
        switch (onInterface->getType()) {
            case NlsrInterface::POINTTOPOINT:
                EV_DETAIL << "(PointToPoint)";
                break;

            case NlsrInterface::POINTTOMULTIPOINT:
                EV_DETAIL << "(PointToMultiPoint)";
                break;

            default:
                EV_DETAIL << "(Unknown)";
                break;
        }
        EV_DETAIL << " (state: "
                  << onInterface->getStateString(onInterface->getState())
                  << ")";
    }
    EV_DETAIL << ".\n";
}

void MessageHandler::printHelloInterestPacket(const NlsrHelloInterest *helloPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending Hello interest packet to " << destination << ". on interface[" << outputIfIndex << "] with contents:\n";
    EV_DETAIL << "  neighbors:\n";
}

void MessageHandler::printHelloDataPacket(const NlsrHelloData *helloPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending Hello data packet to " << destination << " on interface[" << outputIfIndex << "] with contents:\n";
    EV_DETAIL << "  neighbors:\n";
}

void MessageHandler::printSyncInterestPacket(const syncInterest *syncInterestPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending sync Interest packet to " << destination << " on interface[" << outputIfIndex << "] :\n";
}

void MessageHandler::printSyncDataPacket(const syncData *syncDataPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending sync Data packet to " << destination << " on interface[" << outputIfIndex << "] :\n";
}

void MessageHandler::printNameLsaInterestPacket(const NameLsaInterest *nameInterestPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending name Interest packet to " << destination << " on interface[" << outputIfIndex << "] :\n";
}

void MessageHandler::printNameLsaDataPacket(const NameDataPacket *nameDataPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending LSA packet to " << destination << " on interface[" << outputIfIndex << "] :\n";
}

void MessageHandler::printAdjLsaInterestPacket(const AdjLsaInterest *adjInterestPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending adj Interest packet to " << destination << " on interface[" << outputIfIndex << "] :\n";
}

void MessageHandler::printAdjLsaDataPacket(const AdjDataPacket *adjDataPacket, std::string  destination, int outputIfIndex) const
{
    EV_INFO << "Sending adj Data packet to " << destination << " on interface[" << outputIfIndex << "] :\n";
}

} // namespace nlsr
} // namespace inet


