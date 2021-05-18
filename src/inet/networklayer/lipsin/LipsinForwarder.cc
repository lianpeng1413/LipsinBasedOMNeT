/*
 * LipsinForwarder.cpp
 *
 *  Created on: Mar 11, 2021
 *      Author: root
 */
#include "inet/applications/common/SocketTag_m.h"
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/common/INETUtils.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/checksum/TcpIpChecksum.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/common/NextHopAddressTag_m.h"
#include "inet/networklayer/common/TosTag_m.h"
#include "inet/networklayer/contract/IArp.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/lipsin/LipsinHeader_m.h"
#include "inet/networklayer/lipsin/configurator/LipsinConfigReader.h"
#include "inet/queueing/queue/PacketQueue.h"
#include "inet/networklayer/lipsin/LipsinForwarder.h"

#include <regex>
namespace inet {
Define_Module(LipsinForwarder);
Register_Abstract_Class(ISLDistanceChangeDetails);

std::string ISLDistanceChangeDetails::str() const
{
    std::stringstream out;
    out << obj->getFullPath() << " changed distance: " << distance << "\n";
    return out.str();
}
LipsinForwarder::LipsinForwarder()
{
}

LipsinForwarder::~LipsinForwarder()
{
}

void LipsinForwarder::initialize(int stage)
{
    OperationalBase::initialize(stage);

    if(stage == INITSTAGE_LOCAL){
        ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        plt = getModuleFromPar<LipsinLdTable>(par("physicalLinkTableModule"),this);
        vlt = getModuleFromPar<LipsinLdTable>(par("virtualLinkTableModule"),this);
        dlt = getModuleFromPar<LipsinLdTable>(par("downLinkTableModule"),this);
        deletePeriod = par("deletePeriod");
        islCheckInterval = par("islCheckInterval");
        transportInGateBaseId = gateBaseId("transportIn");
        host = getContainingNode(this);
        islDistanceTimer = new cMessage("islDistanceTimer");
        numMulticast = numLocalDeliver = numDropped = numUnroutable = numForwarded = 0;
        registerService(Protocol::lipsin, gate("transportIn"), gate("queueIn"));
        registerProtocol(Protocol::lipsin, gate("queueOut"), gate("transportOut"));

        //NetFilter:
        hooks.clear();
        queuedDatagramsForHooks.clear();
    }else if(stage == INITSTAGE_NETWORK_CONFIGURATION){
        cXMLElement *lipsinConfig = par("lipsinConfig");
        lipsin::LipsinConfigReader configReader(this,ift,plt,dlt,vlt,deletePeriod);
        if (!configReader.loadConfigFromXML(lipsinConfig))
            throw cRuntimeError("Error reading LIPSIN configuration from %s", lipsinConfig->getSourceLocation());

    }
}

void LipsinForwarder::subscribe()
{
    host->subscribe(interfaceCreatedSignal, this);
    host->subscribe(interfaceDeletedSignal, this);
    host->subscribe(interfaceStateChangedSignal, this);
    host->subscribe(congestionChangedSignal, this);
    host->subscribe(islDistanceMeasureSignal, this);
}

void LipsinForwarder::unsubscribe()
{
    host->unsubscribe(interfaceCreatedSignal, this);
    host->unsubscribe(interfaceDeletedSignal, this);
    host->unsubscribe(interfaceStateChangedSignal, this);
    host->unsubscribe(congestionChangedSignal, this);
    host->unsubscribe(islDistanceMeasureSignal, this);
}

void LipsinForwarder::handleRegisterService(const Protocol& protocol, cGate *out, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterService");
}

void LipsinForwarder::handleRegisterProtocol(const Protocol& protocol, cGate *in, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterProtocol");
    if (in->isName("transportIn"))
            upperProtocols.insert(&protocol);
}

void LipsinForwarder::refreshDisplay() const
{
    OperationalBase::refreshDisplay();

    char buf[80] = "";
    if (numForwarded > 0)
        sprintf(buf + strlen(buf), "fwd:%d ", numForwarded);
    if (numLocalDeliver > 0)
        sprintf(buf + strlen(buf), "up:%d ", numLocalDeliver);
    if (numMulticast > 0)
        sprintf(buf + strlen(buf), "mcast:%d ", numMulticast);
    if (numDropped > 0)
        sprintf(buf + strlen(buf), "DROP:%d ", numDropped);
    if (numUnroutable > 0)
        sprintf(buf + strlen(buf), "UNROUTABLE:%d ", numUnroutable);
    getDisplayString().setTagArg("t", 0, buf);
}

void LipsinForwarder::handleRequest(Request *request)
{ // TODO:
    auto ctrl = request->getControlInfo();
    if(ctrl == nullptr)
        throw cRuntimeError("Request '%s' arrived without controlinfo",request->getName());
}

void LipsinForwarder::handleMessageWhenUp(cMessage *msg)
{
    if (msg == islDistanceTimer){
        emit(checkISLDistanceSignal,msg);
        simtime_t next = simTime() + islCheckInterval;
        scheduleAt(next, islDistanceTimer);
    }
    else if (msg->arrivedOn("transportIn")) {    //TODO packet->getArrivalGate()->getBaseId() == transportInGateBaseId
        if (auto request = dynamic_cast<Request *>(msg))
            handleRequest(request);
        else{
            EV_INFO << "Received " << msg << " from Higher Network.\n";
            handlePacketFromHL(check_and_cast<Packet*>(msg));
        }
    }
    else if (msg->arrivedOn("queueIn")) {    // from network
        EV_INFO << "Received " << msg << " from network.\n";
        handleIncomingDatagram(check_and_cast<Packet*>(msg));
    }
    else
        throw cRuntimeError("message arrived on unknown gate '%s'", msg->getArrivalGate()->getName());
}

const InterfaceEntry *LipsinForwarder::getSourceInterface(Packet *packet)
{
    auto tag = packet->findTag<InterfaceInd>();
    return tag != nullptr ? ift->getInterfaceById(tag->getInterfaceId()) : nullptr;
}

const InterfaceEntry *LipsinForwarder::getDestInterface(Packet *packet)
{
    auto tag = packet->findTag<InterfaceReq>();
    return tag != nullptr ? ift->getInterfaceById(tag->getInterfaceId()) : nullptr;
}

void LipsinForwarder::encapsulate(Packet *packet)
{
    //the function is used to encapsulate LIPSIN Header
    //but the  LIPSIN Header should be encapsulate at higher layer
}
void LipsinForwarder::decapsulate(Packet *packet){
    //TODO:decapsulate
    //the function is used to decapsulate LIPSIN Header

}
void LipsinForwarder::handleIncomingDatagram(Packet *packet){
    //TODO:handleIncomingDatagram
    packet->trim();
    auto & head = packet->removeAtFront<LipsinHeader>();
    for(int i=0;i<dlt->getNumLds();i++){
        LipsinLdEntry * downLdEntry = dlt->getLd(i);
        int nowlinkId = downLdEntry->getLinkId();
        if(head->preRouteContains(nowlinkId)){
            if(downLdEntry->getLipsinLdTable() == plt){
                head->addLinkToHadRoute(nowlinkId); //add the link Id into the BF[1]
//                EV_INFO<<"Physical Link DOWN ::BF[1] add physical link id:"<< nowlinkId<<endl;
            }
            else{
                InterfaceEntry* intfEntry = downLdEntry->getInterfaceEntry();
                std::vector<LipsinLdEntry*> relatedLdEntryVector = plt->containsIntf(intfEntry);
                if(relatedLdEntryVector.size() > 0){
                    head->addLinkToHadRoute(relatedLdEntryVector[0]->getLinkId());
//                    EV_INFO<<"Virtual Link DOWN::BF[1] add physical link id:"<< relatedLdEntryVector[0]->getLinkId()<<endl;
//                    head->addLinkToPreRoute(relatedLdEntryVector[0]->getLinkId());
                }
            }
        }
    }
    packet->insertAtFront(head);
    for(int i=0;i<plt->getNumLds();i++){
        LipsinLdEntry* phyLdEntry = plt->getLd(i);
        InterfaceEntry* intfEntry = phyLdEntry->getInterfaceEntry();
        int nowlinkId = phyLdEntry->getLinkId();
        if(head->preRouteContains(nowlinkId) && intfEntry->isUp()){
            //forwarding to this intfEntry
            EV_INFO << "the BF[0] hit link Id = " << nowlinkId <<endl;
            if(!intfEntry->findNonce(head->getNonce())){
                sendDatagramToOutput(packet->dup(),intfEntry->getInterfaceId());
                intfEntry->insertNonce(head->getNonce());
                EV_INFO<<"send this pkt and insert Nonce" <<endl;
            }else{
                EV_INFO<<"hit nonceTable and skip" <<endl;
            }
        }
    }
    for(int i=0;i<vlt->getNumLds();i++){
        LipsinLdEntry* virLdEntry = vlt->getLd(i);
        InterfaceEntry* intfEntry = virLdEntry->getInterfaceEntry();
        int nowlinkId = virLdEntry->getLinkId();
        if(head->hadRouteContains(nowlinkId) && intfEntry->isUp()){
            //forwarding to this intfEntry
            EV_INFO << "the BF[1] hit link Id = " << nowlinkId <<endl;
            if(!intfEntry->findNonce(head->getNonce())){
                sendDatagramToOutput(packet->dup(),intfEntry->getInterfaceId());
                intfEntry->insertNonce(head->getNonce());
                EV_INFO<<"send this pkt and insert Nonce" <<endl;
            }else{
                EV_INFO<<"hit nonceTable and skip" <<endl;
            }

        }
    }
    sendPacketToHL(packet);
//    packet->trim();
//    delete packet;

    //first : find the missing link
    //second : adjust the header BF[1]
    //third : search the physical & virtual up link and send the packet if match
}
void LipsinForwarder::sendPacketToHL(Packet *packet){
    const auto& lipsinHeader = packet->removeAtFront<LipsinHeader>();
    const auto& ipv4Header = packet->peekAtFront<Ipv4Header>();
    auto transportProtocol = ProtocolGroup::ipprotocol.getProtocol(ipv4Header->getProtocolId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(transportProtocol);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(transportProtocol);
    packet->insertAtFront(lipsinHeader);
    send(packet, "transportOut");
}
void LipsinForwarder::handlePacketFromHL(Packet *packet){
    //TODO:handleIncomingDatagram
    packet->trim();
    auto & head = packet->removeAtFront<LipsinHeader>();
    for(int i=0;i<dlt->getNumLds();i++){
        LipsinLdEntry * downLdEntry = dlt->getLd(i);
        int nowlinkId = downLdEntry->getLinkId();
        if(head->preRouteContains(nowlinkId)){
            if(downLdEntry->getLipsinLdTable() == plt)
                head->addLinkToHadRoute(nowlinkId); //add the link Id into the BF[1]
            else{
                InterfaceEntry* intfEntry = downLdEntry->getInterfaceEntry();
                std::vector<LipsinLdEntry*> relatedLdEntryVector = plt->containsIntf(intfEntry);
                if(relatedLdEntryVector.size() > 0){
                    head->addLinkToHadRoute(relatedLdEntryVector[0]->getLinkId());
//                    head->addLinkToPreRoute(relatedLdEntryVector[0]->getLinkId());
                }
            }
        }
    }
    packet->insertAtFront(head);
    for(int i=0;i<plt->getNumLds();i++){
        LipsinLdEntry* phyLdEntry = plt->getLd(i);
        InterfaceEntry* intfEntry = phyLdEntry->getInterfaceEntry();
        int nowlinkId = phyLdEntry->getLinkId();
        if(head->preRouteContains(nowlinkId) && intfEntry->isUp()){
            //forwarding to this intfEntry
            EV_INFO << "the BF[0] hit link Id = " << nowlinkId <<endl;
            if(!intfEntry->findNonce(head->getNonce())){
                sendDatagramToOutput(packet->dup(),intfEntry->getInterfaceId());
                intfEntry->insertNonce(head->getNonce());
                EV_INFO<<"send this pkt and insert Nonce" <<endl;
            }else{
                EV_INFO<<"hit nonceTable and skip" <<endl;
            }
        }
    }
    for(int i=0;i<vlt->getNumLds();i++){
        LipsinLdEntry* virLdEntry = vlt->getLd(i);
        InterfaceEntry* intfEntry = virLdEntry->getInterfaceEntry();
        int nowlinkId = virLdEntry->getLinkId();
        if(head->hadRouteContains(nowlinkId) && intfEntry->isUp()){
            //forwarding to this intfEntry
            EV_INFO << "the BF[1] hit link Id = " << nowlinkId <<endl;
            if(!intfEntry->findNonce(head->getNonce())){
                sendDatagramToOutput(packet->dup(),intfEntry->getInterfaceId());
                intfEntry->insertNonce(head->getNonce());
                EV_INFO<<"send this pkt and insert Nonce" <<endl;
            }else{
                EV_INFO<<"hit nonceTable and skip" <<endl;
            }

        }
    }
    packet->trim();
    delete packet;
}

void LipsinForwarder::sendDatagramToOutput(Packet *packet,int nic)
{
    //according to the interface Tag from the packet
    // output to the out interface
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(nic);
    const InterfaceEntry *ie = ift->getInterfaceById(packet->getTag<InterfaceReq>()->getInterfaceId());
    packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
    sendPacketToNIC(packet);

}

void LipsinForwarder::sendPacketToNIC(Packet *packet)
{
    EV_INFO << "Sending " << packet << " to output interface = " << ift->getInterfaceById(packet->getTag<InterfaceReq>()->getInterfaceId())->getInterfaceName() << ".\n";
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin);
    packet->addTagIfAbsent<DispatchProtocolInd>()->setProtocol(&Protocol::lipsin);
    delete packet->removeTagIfPresent<DispatchProtocolReq>();
    ASSERT(packet->findTag<InterfaceReq>() != nullptr);
    send(packet, "queueOut");
}

void LipsinForwarder::handleStartOperation(LifecycleOperation *operation)
{
    subscribe();
    start();
}

void LipsinForwarder::handleStopOperation(LifecycleOperation *operation)
{
    // TODO: stop should send and wait pending packets
    unsubscribe();
    stop();
}

void LipsinForwarder::handleCrashOperation(LifecycleOperation *operation)
{
    unsubscribe();
    stop();
}

void LipsinForwarder::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
    Enter_Method("LipsinForwarder::receiveSignal");
    // TODO: when receive the link state
    const InterfaceEntry *ie;
    const InterfaceEntryChangeDetails *change;
    const queueing::CongestionChangeDetails *congestionChange;
    const ISLDistanceChangeDetails *distanceChange;

    if (signalID == interfaceCreatedSignal) {
        // configure interface for RIP
        ie = check_and_cast<const InterfaceEntry *>(obj);
        if (ie->isMulticast() && !ie->isLoopback()) {
            // TODO : interface became
        }
    }
    else if (signalID == interfaceDeletedSignal) {
        ie = check_and_cast<const InterfaceEntry *>(obj);
        // TODO
    }
    else if (signalID == interfaceStateChangedSignal) {
        change = check_and_cast<const InterfaceEntryChangeDetails *>(obj);
        auto fieldId = change->getFieldId();
        if (fieldId == InterfaceEntry::F_STATE || fieldId == InterfaceEntry::F_CARRIER) {
            ie = change->getInterfaceEntry();
            if (!ie->isUp()){//up -> down
                std::vector<LipsinLdEntry *>  relatedPhyLdEntry = plt->containsIntf(ie),
                        relatedVirLdEntry = vlt->containsIntf(ie);
                for(int i=0;i<relatedPhyLdEntry.size();i++)
                    dlt->addEntry(relatedPhyLdEntry[i]);
                for(int i=0;i<relatedVirLdEntry.size();i++)
                    dlt->addEntry(relatedVirLdEntry[i]);
                EV_INFO << "Successfully handle the change of interfaceEntry "<<ie->str()<<  " from UP to DOWN"<<endl;
            }
            else {
                // down -> up
                dlt->removeEntryByIntf(ie);
                EV_INFO << "Successfully handle the change of interfaceEntry "<<ie->str()<<  " from DOWN to up"<<endl;
                            // interface went back online. Do nothing!
            }
        }
    }
    else if(signalID == congestionChangedSignal){
        congestionChange = check_and_cast<const queueing::CongestionChangeDetails *>(obj);
        std::cout<<"received signals of congestion changing "<<obj->str()<<std::endl;
        std::string fullPath(congestionChange->getcObject()->getFullPath());
        std::smatch match;
        std::regex r("([[:w:]]+).LEO([0-9]+).([a-z]+)\\[([0-9])\\]");//OsgEarthNet.LEO0.eth[0]
        bool found = regex_search(fullPath,match,r);
        std::stringstream ss;
        ss<<match[3].str()<<match[4].str();
        char ifName[4];
        ss>>ifName;
        InterfaceEntry *ie = ift->findInterfaceByName(ifName);
        int nowState = congestionChange->getCongestionState();
        if(nowState != 4){
            if(ie != nullptr){
                // down -> up
                std::cout<<"nowState: "<<nowState<<" maybe down->up AND update this interface " << ifName <<  " Entry Cost"<<std::endl;
                dlt->removeEntryByIntf(ie);
                int nowCost = nowState;
                vlt->updateEntryCost(ie, nowCost);
                plt->updateEntryCost(ie, nowCost);
            }
        }else{
            //up -> down (very congested!!!)
            if(ie != nullptr){
                std::cout<<"nowState: "<< nowState <<" shutdown all Entry about this interface "<< ifName << std::endl;
                std::vector<LipsinLdEntry *>  relatedPhyLdEntry = plt->containsIntf(ie),
                        relatedVirLdEntry = vlt->containsIntf(ie);
                for(int i=0;i<relatedPhyLdEntry.size();i++)
                    dlt->addEntry(relatedPhyLdEntry[i]);
                for(int i=0;i<relatedVirLdEntry.size();i++)
                    dlt->addEntry(relatedVirLdEntry[i]);
            }
        }
    }
    else if(signalID == islDistanceMeasureSignal){
        distanceChange = check_and_cast<const ISLDistanceChangeDetails *>(obj);
        std::cout<< distanceChange->getcObject()->getFullPath() << " emit a signal: ISL distance = " << distanceChange->getDistance() << std::endl;
        std::string fullPath(distanceChange->getcObject()->getOwner()->getFullPath());
        std::smatch match;
        std::regex r("([[:w:]]+).LEO([0-9]+).([a-z]+)g\\$o\\[([0-9])\\]");//OsgEarthNet.LEO0.eth[0]
        bool found = regex_search(fullPath,match,r);
        std::string ifname = match[3].str() + match[4].str();
        InterfaceEntry *ie = ift->findInterfaceByName(ifname.c_str());
        vlt->updateEntryDistance(ie, distanceChange->getDistance());
    }
    else
        throw cRuntimeError("Unexpected signal: %s", getSignalName(signalID));
}

INetfilter::IHook::Result LipsinForwarder::datagramPreRoutingHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result LipsinForwarder::datagramForwardHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result LipsinForwarder::datagramPostRoutingHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result LipsinForwarder::datagramLocalInHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result LipsinForwarder::datagramLocalOutHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}

void LipsinForwarder::registerHook(int priority, IHook *hook)
{
}


void LipsinForwarder::unregisterHook(IHook *hook)
{

}

//in order to fix the problem of "Virtual functions are pure within inet::LipsinForwarder"
void LipsinForwarder::dropQueuedDatagram(const Packet *datagram)
{

}

void LipsinForwarder::reinjectQueuedDatagram(const Packet *datagram)
{

}
void LipsinForwarder::start()
{
    simtime_t next = simTime() + islCheckInterval;
    scheduleAt(next, islDistanceTimer);

}

void LipsinForwarder::stop()
{
    cancelEvent(islDistanceTimer);
}
void LipsinForwarder::flush()
{
    cancelEvent(islDistanceTimer);
}
} /* namespace inet */
