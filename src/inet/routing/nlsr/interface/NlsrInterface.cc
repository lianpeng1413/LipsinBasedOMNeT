/*
 * NlsrInterface.cc
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */


#include <memory.h>
#include <vector>

#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/interface/NlsrInterfaceStateDown.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet {

namespace nlsr {

// FIXME!!! Should come from a global unique number generator module.
unsigned long NlsrInterface::nameLSASeqNumberInitSeed = 0;
unsigned long NlsrInterface::adjLSASeqNumberInitSeed  = 0;

NlsrInterface::NlsrInterface(NlsrInterface::NlsrInterfaceType ifType) :
    interfaceType(ifType),
    interfaceMode(ACTIVE),
    interfaceName(""),
    ifIndex(0),
    mtu(1400),
    areaID(BACKBONE_AREAID),
    transitAreaID(BACKBONE_AREAID),
    helloInterval(3),
    routerDeadInterval(10),
    interfaceOutputCost(1),
    parentArea(nullptr)
{
    state = new InterfaceStateDown;
    previousState = nullptr;
    helloTimer = new cMessage("Interface::InterfaceHelloTimer", INTERFACE_HELLO_TIMER);
    helloTimer->setContextPointer(this);
}

NlsrInterface::~NlsrInterface()
{
    if(parentArea){
        MessageHandler *messageHandler = parentArea->getRouter()->getMessageHandler();
        messageHandler->clearTimer(helloTimer);
    }
    delete helloTimer;

    if (previousState)
        delete previousState;
    delete state;
//    for (uint32_t i = 0; i < neighboringRouters.size(); i++)
//        delete neighboringRouters[i];
}

const char *NlsrInterface::getTypeString(NlsrInterfaceType intfType)
{
    switch (intfType) {
        case UNKNOWN_TYPE:
            return "Unknown";

        case POINTTOPOINT:
            return "PointToPoint";

        case POINTTOMULTIPOINT:
            return "PointToMultiPoint";

        default:
            ASSERT(false);
            break;
    }
    return "";
}

const char *NlsrInterface::getModeString(NlsrInterfaceMode intfMode)
{
    switch (intfMode) {
        case ACTIVE:
            return "Active";

        case PASSIVE:
            return "Passive";

        case NO_NLSR:
            return "NoNLSR";

        default:
            ASSERT(false);
            break;
    }
    return "";
}

void NlsrInterface::setIfIndex(IInterfaceTable *ift, int index)
{
    ifIndex = index;
}

void NlsrInterface::changeState(NlsrInterfaceState *newState, NlsrInterfaceState *currentState)
{
    EV_INFO << "Changing the state of interface " << this->getIfIndex() <<
            " from '" << getStateString(currentState->getState()) <<
            "' to '" << getStateString(newState->getState()) << "'" << std::endl;

    if (previousState != nullptr) {
        delete previousState;
    }
    state = newState;
    previousState = currentState;
}

void NlsrInterface::processEvent(NlsrInterface::NlsrInterfaceEventType event)
{
    state->processEvent(this, event);
}

void NlsrInterface::reset()
{
    this->getIfIndex();
    MessageHandler *messageHandler = parentArea->getRouter()->getMessageHandler();
    messageHandler->clearTimer(helloTimer);

    long neighborCount = neighboringRouters.size();
    for (long i = 0; i < neighborCount; i++) {
        neighboringRouters[i]->processEvent(Neighbor::KILL_NEIGHBOR);

        iName neighborName = neighboringRouters[i]->getNeighborName();

        //Update local AdjLsa: remove neighbor info from local adjList
        iName localAdjName;
        localAdjName.set(this->getArea()->getRouter()->getRouterID().str().erase(0, 1), "ADJLSA", std::to_string(0));
        auto localAdjLsa = this->getArea()->findAdjLsa(localAdjName);
        auto seqNo = localAdjLsa->getHeader().getSeqNo();
//        auto adjList = localAdjLsa->getM_adlForUpdate();
//        adjList->deleteNeighbor(neighborName);

        localAdjLsa->getM_adlForUpdate()->deleteNeighbor(neighborName);//Delete neighbor from adjList
        localAdjLsa->getHeaderForUpdate().setSeqNo(seqNo + 1);
        this->getArea()->installAdjLsaToLsdb(localAdjLsa);
    }

    pendingRequestAdjLsaName.clear();
    pendingRequestNameLsaName.clear();
    neighboringRouters.clear();
    neighboringRoutersByName.clear();
}

void NlsrInterface::sendHelloInterestPacket(iName destination, short ttl)
{
    const auto& helloInterest = makeShared<NlsrHelloInterest>(); // create header

    helloInterest->setType(HELLO_INTEREST);
    helloInterest->setHelloInterval(helloInterval);
    helloInterest->setRouterDeadInterval(routerDeadInterval);
    helloInterest->setHopCount(0);
    helloInterest->setSeqNo(0);
    helloInterest->setCanBePrefix(true);
    helloInterest->setMustBeFresh(true);
    helloInterest->setInterestLifetimeMs(4000);
    helloInterest->setHopLimit(1);

    //Get local router name
    iName localRouter = parentArea->getRouter()->getRouterID();

    // Create Hello Interest name: /Neighbor/HelloINFO/localRouter.
    iName interestName;
    interestName.set(destination.str().erase(0, 1), "HELLOINFO", localRouter.str().erase(0, 1)); //Generate interest name

    helloInterest->setInterestName(interestName);
    Packet *pk = new Packet();
    pk->insertAtBack(helloInterest);

    this->setNeighborMac(inet::MacAddress::BROADCAST_ADDRESS);
    parentArea->getRouter()->getMessageHandler()->sendPacket(pk, destination, this, 1);
    pk->trim();
    delete pk;
}

Neighbor *NlsrInterface::getNeighborByName(iName neighborName)
{
    auto neighborIt = neighboringRoutersByName.find(neighborName);
    if (neighborIt != neighboringRoutersByName.end())
        return neighborIt->second;
    else
        return nullptr;
}

void NlsrInterface::addNeighbor(Neighbor *neighbor)
{
    neighboringRoutersByName[neighbor->getNeighborName()] = neighbor;
    neighbor->setInterface(this);
    neighboringRouters.push_back(neighbor);
}

void NlsrInterface::removeNeighbor(iName neighbor)
{
    for (auto it = neighboringRouters.begin();it != neighboringRouters.end(); it++) {
        if ((*it)->getNeighborName() == neighbor){
            delete (*it);
            it = neighboringRouters.erase(it);//delete item.
        }
    }
}

NlsrInterface::NlsrInterfaceStateType NlsrInterface::getState() const
{
    return state->getState();
}

const char *NlsrInterface::getStateString(NlsrInterface::NlsrInterfaceStateType stateType)
{
    switch (stateType) {
        case DOWN_STATE:
            return "Down";

        case POINTTOPOINT_STATE:
            return "point-to-point state";

        case UNKNOWN_STATE:
            return "unknown";

        default:
            ASSERT(false);
            break;
    }
    return "";
}

bool NlsrInterface::hasAnyNeighborInStates(int states) const
{
    for (uint32_t i = 0; i < neighboringRouters.size(); i++) {
        Neighbor::NeighborStateType neighborState = neighboringRouters[i]->getState();
        if (neighborState & states)
            return true;
    }
    return false;
}

void NlsrInterface::addToPendingRequestAdjLsaNameList(iName& PRIN)
{
    pendingRequestAdjLsaName.push_back(PRIN);
}

void NlsrInterface::addToPendingRequestNameLsaNameList(iName& PRIN)
{
    pendingRequestNameLsaName.push_back(PRIN);
}

// It might will include many interest names in adj list which should be sync.
void NlsrInterface::sendAdjLSAInterestPacket(iName requestName, iName destination, short ttl, Neighbor * neighbor)
{//adj interest name: /Neighbor/ADJINTERESTLSA/<localrouterName>
    const auto& adjLsaInterestPacket = makeShared<AdjLsaInterest>();//create header

    //Generate interest name and packet
    iName adjInterestName;
    std::string tag, prefix, tail;
    tag = destination.getTail();
    prefix += "ADJINTERESTLSA";
    tail = destination.getTag();
    adjInterestName.set(tag, prefix, tail);

    adjLsaInterestPacket->setInterestName(adjInterestName); // SET nlsrPacketBase INTEREST NAME
    adjLsaInterestPacket->setVersion(2);
    adjLsaInterestPacket->setType(ADJ_LSA_INTEREST);
    adjLsaInterestPacket->setHopCount(ttl);
    adjLsaInterestPacket->setSeqNo(adjLSASeqNumber);
    adjLsaInterestPacket->setCanBePrefix(true);
    adjLsaInterestPacket->setMustBeFresh(true);
    adjLsaInterestPacket->setInterestLifetimeMs(4000);
    adjLsaInterestPacket->setHopLimit(1);

    //B maxPacketSize = NLSR_ADJLSA_INTEREST_LENGTH;
    B packetSize = NLSR_HEADER_LENGTH + B(80);

    if (!pendingRequestAdjLsaName.empty()) {
        auto it = pendingRequestAdjLsaName.begin();
        while ( it != pendingRequestAdjLsaName.end()) {
            iName requestAdjLsa = (*it);
            NlsrLsaInterest intersts;

            intersts.lsType = adjLsaInterestPacket->getType();
            intersts.interestName = requestAdjLsa;

            adjLsaInterestPacket->setInterestsArraySize(1);
            adjLsaInterestPacket->setInterests(0, intersts);

            packetSize += INAME_LENGTH;
            adjLsaInterestPacket->setPacketLengthField(B(packetSize).get());
            adjLsaInterestPacket->setChunkLength(NLSR_ADJLSA_INTEREST_LENGTH);

            Packet *pk = new Packet();
            pk->insertAtBack(adjLsaInterestPacket);

            EV_INFO << "Lsa Interest:" << requestAdjLsa.str() << "\n";

            MessageHandler *messageHandler = parentArea->getRouter()->getMessageHandler();
//            if (neighbor->getState() > Neighbor::DOWN_STATE) {//TODO
            iName nextNode;
            nextNode.transName(destination.getTail());
            EV_INFO << "Lsa Interest:" << requestAdjLsa.str() << "\n";
            messageHandler->sendPacket(pk, nextNode, this, 1);
//            }
            delete pk;
            it++;
        }
    }
    //Delete pendingRequestadjLsaName vector after sending adjLSAs
    pendingRequestAdjLsaName.clear();
}

void NlsrInterface::sendNameLSAInterestPacket(iName requestName, iName destination, short ttl, Neighbor * neighbor)
{//name: /Neighbor/NAMEINTERESTLSA/<localrouterName>
    const auto& nameLsaInterestPacket = makeShared<NameLsaInterest>();

    //Generate interest name and packet
    iName nameInterestName;
    std::string tag, prefix, tail;
    tag = destination.getTail();
    prefix += "ADJINTERESTLSA";
    tail = parentArea->getRouter()->getRouterID().str();
    nameInterestName.set(tag, prefix, tail.erase(0, 1));

    nameLsaInterestPacket->setInterestName(nameInterestName); // SET INTEREST NAME
    nameLsaInterestPacket->setVersion(2);
    nameLsaInterestPacket->setType(NAME_LSA_INTEREST);
    nameLsaInterestPacket->setHopCount(ttl);
    nameLsaInterestPacket->setSeqNo(nameLSASeqNumber);
    nameLsaInterestPacket->setCanBePrefix(true);
    nameLsaInterestPacket->setMustBeFresh(true);
    nameLsaInterestPacket->setInterestLifetimeMs(4000);
    nameLsaInterestPacket->setHopLimit(1);

    //B maxPacketSize = NLSR_NAMELSA_INTEREST_LENGTH;
    B packetSize = NLSR_HEADER_LENGTH + B(24);

    if (!pendingRequestNameLsaName.empty()) {
        auto it = pendingRequestNameLsaName.begin();
        while (it != pendingRequestNameLsaName.end()) {
            iName requestNameLsa = (*it);
            NlsrLsaInterest intersts;
            unsigned long interestNum = 0;
            intersts.lsType = nameLsaInterestPacket->getType();
            intersts.interestName = requestNameLsa;

            EV_INFO << "requst name lsa: " << requestNameLsa.str() << endl;

            nameLsaInterestPacket->setInterestsArraySize(1);
            nameLsaInterestPacket->setInterests(interestNum, intersts);
            packetSize += INAME_LENGTH;

            nameLsaInterestPacket->setPacketLengthField(B(packetSize).get());
            nameLsaInterestPacket->setChunkLength(NLSR_ADJLSA_INTEREST_LENGTH);

            Packet *pk = new Packet();
            pk->insertAtBack(nameLsaInterestPacket);

            MessageHandler *messageHandler = parentArea->getRouter()->getMessageHandler();
//            if (neighbor->getState() > Neighbor::DOWN_STATE) {
            iName nextNode;
            nextNode.transName(destination.getTail());
            messageHandler->sendPacket(pk, nextNode, this, 1);
//            }
            delete pk;
            it++;
        }
    }
    //Delete pendingRequestNameLsaName vector after sending nameLSAs
    pendingRequestNameLsaName.clear();
}

bool NlsrInterface::getWhetherFull()
{
    if(pendingRequestAdjLsaName.empty() && pendingRequestNameLsaName.empty())
        return true;
    else
        return false;
}

void NlsrInterface::initFirstAdjacency()
{
    adjLSASeqNumber = getUniqueULong();
    firstAdjacencyInited = true;
}

void NlsrInterface::initFirstName()
{
    nameLSASeqNumber = getNameULong();
    firstNameInited = true;
}

unsigned long NlsrInterface::getUniqueULong()
{
    // FIXME!!! Should come from a global unique number generator module.
    return adjLSASeqNumberInitSeed++;
}

unsigned long NlsrInterface::getNameULong()
{
    // FIXME!!! Should come from a global unique number generator module.
    return nameLSASeqNumberInitSeed++;
}

std::ostream& operator<<(std::ostream& stream, const NlsrInterface& intf)
{
    std::string neighbors = "";
    for(auto &neighbor : intf.neighboringRouters) {

    }

    return stream << "name: " << intf.getInterfaceName() << " "
            << "index: " << intf.ifIndex << " "
            << "type: '" << intf.getTypeString(intf.interfaceType) << "' "
            << "MTU: " << intf.mtu << " "
            << "state: '" << intf.getStateString(intf.state->getState()) << "' "
            << "mode: '" << intf.getModeString(intf.interfaceMode) << "' "
            << "cost: " << intf.interfaceOutputCost << " "

            << "helloInterval: " << intf.helloInterval << " "
            << "routerDeadInterval: " << intf.routerDeadInterval << " "
            << "neighboringRouters: " << ((neighbors == "") ? "<none>(down)" : neighbors);
}

} // namespace nlsr
} // namespace inet


