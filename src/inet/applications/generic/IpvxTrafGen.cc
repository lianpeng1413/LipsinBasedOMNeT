//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004-2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/applications/generic/IpvxTrafGen.h"
#include "inet/applications/generic/LipsinRoute/LipsinRouteConfigurator.h"
#include "inet/applications/generic/LipsinRoute/LipsinTopoManager.h"

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/arp/ipv4/ArpPacket_m.h"
#include "inet/networklayer/common/DscpTag_m.h"
#include "inet/networklayer/common/EcnTag_m.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/common/L3Tools.h"
#include "inet/networklayer/common/MulticastTag_m.h"
#include "inet/networklayer/common/NextHopAddressTag_m.h"
#include "inet/networklayer/common/TosTag_m.h"
#include "inet/networklayer/contract/IArp.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/ipv4/Ipv4SocketCommand_m.h"
#include "inet/networklayer/ipv4/IIpv4RoutingTable.h"
#include "inet/networklayer/ipv4/IcmpHeader_m.h"
#include "inet/networklayer/ipv4/Ipv4.h"
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"
#include "inet/networklayer/ipv4/Ipv4OptionsTag_m.h"
#include "inet/networklayer/lipsin/LipsinHeader_m.h"

namespace inet {

Define_Module(IpvxTrafGen);


std::vector<const Protocol *> IpvxTrafGen::allocatedProtocols;

IpvxTrafGen::IpvxTrafGen()
{
}

IpvxTrafGen::~IpvxTrafGen()
{
    cancelAndDelete(timer);
    cancelAndDelete(topoManager->getUpdateTimer());
    delete routeInfoTable;
    delete topoManager;
}

void IpvxTrafGen::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        int protocolId = par("protocol");
        hasLipsin = par("hasLipsin");
        if (protocolId < 143 || protocolId > 254)
            throw cRuntimeError("invalid protocol id %d, accepts only between 143 and 254", protocolId);
        protocol = ProtocolGroup::ipprotocol.findProtocol(protocolId);
        if (!protocol) {
            std::string name = "prot_" + std::to_string(protocolId);
            protocol = new Protocol(name.c_str(), name.c_str());
            allocatedProtocols.push_back(protocol);
            ProtocolGroup::ipprotocol.addProtocol(protocolId, protocol);
        }
        numPackets = par("numPackets");
        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");

        packetLengthPar = &par("packetLength");
        sendIntervalPar = &par("sendInterval");

        timer = new cMessage("sendTimer");

        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        routeInfoTable = new lipsin::LinkInfoTable(this);
        lipsin::LipsinRouteConfigurator configurator(getContainingNode(this),routeInfoTable);
        cXMLElement *lipsinConfig = par("lipsinConfig"),*script = par("script");
        if (!configurator.loadConfigFromXML(lipsinConfig))
                    throw cRuntimeError("IpvxTrafGen Error reading LIPSIN configuration from %s", lipsinConfig->getSourceLocation());
        routeInfoTable->reCalculate(&linkSetById);
        for(const auto &linkSetMap:linkSetById){
            std::cout<< "destination "<< linkSetMap.first << std::endl;
            for(const auto & link:*linkSetMap.second) std::cout<<link<<"\t";
            std::cout<<std::endl;
        }
        topoManager = new lipsin::LipsinTopoManager(routeInfoTable,this,&linkSetById);
        topoManager->loadConfigFromXML(script);
        registerService(*protocol, nullptr, gate("ipIn"));
        registerProtocol(*protocol, gate("ipOut"), nullptr);
    }
}

void IpvxTrafGen::startApp()
{
    if (isEnabled())
        scheduleNextPacket(-1);
}

void IpvxTrafGen::handleMessageWhenUp(cMessage *msg)
{
    std::string msgName(msg->getName()),timeName(topoManager->getUpdateTimer()->getName());
    if (msg == timer) {
        if (msg->getKind() == START) {
            destAddresses.clear();
            const char *destAddrs = par("destAddresses");
            cStringTokenizer tokenizer(destAddrs);
            const char *token;
            while ((token = tokenizer.nextToken()) != nullptr) {
                L3Address result;
                L3AddressResolver().tryResolve(token, result);
                if (result.isUnspecified())
                    EV_ERROR << "cannot resolve destination address: " << token << endl;
                else
                    destAddresses.push_back(result);
            }
        }
        if (!destAddresses.empty()) {
            sendPacket();
            if (isEnabled())
                scheduleNextPacket(simTime());
        }
    }
    else if(msgName == timeName){
        delete msg;
        topoManager->changeTopo();
    }
    else
        processPacket(check_and_cast<Packet *>(msg));
}

void IpvxTrafGen::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[40];
    sprintf(buf, "rcvd: %d pks\nsent: %d pks", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void IpvxTrafGen::scheduleNextPacket(simtime_t previous)
{
    simtime_t next;
    if (previous == -1) {
        next = simTime() <= startTime ? startTime : simTime();
        timer->setKind(START);
    }
    else {
        next = previous + *sendIntervalPar;
        timer->setKind(NEXT);
    }
    if (stopTime < SIMTIME_ZERO || next < stopTime)
        scheduleAt(next, timer);
}

void IpvxTrafGen::cancelNextPacket()
{
    cancelEvent(timer);
}

bool IpvxTrafGen::isEnabled()
{
    return numPackets == -1 || numSent < numPackets;
}

L3Address IpvxTrafGen::chooseDestAddr()
{
    int k = intrand(destAddresses.size());
    return destAddresses[k];
}

void IpvxTrafGen::sendPacket()
{
    char msgName[32];
    sprintf(msgName, "appData-%d", numSent);

    Packet *packet = new Packet(msgName);
    const auto& payload = makeShared<ByteCountChunk>(B(*packetLengthPar));
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
    packet->insertAtBack(payload);

    L3Address destAddr = chooseDestAddr();

    IL3AddressType *addressType = destAddr.getAddressType();
    packet->addTag<PacketProtocolTag>()->setProtocol(protocol);
    packet->addTag<L3AddressReq>()->setDestAddress(destAddr);


    if(hasLipsin){
        encapsulateIpv4(packet);
        encapsulateLipsin(packet);
        packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::lipsin);
//        delete packet->removeTagIfPresent<DispatchProtocolReq>();
    }
    EV_INFO << "Sending packet: ";
    printPacket(packet);
    emit(packetSentSignal, packet);
    send(packet, "ipOut");
    numSent++;
}
void IpvxTrafGen::preRoute(Packet *packet,int dest){
    const auto& lipsinHeader = makeShared<LipsinHeader>();
    std::list<int> *links = linkSetById[dest];
    for(auto link:*links){
        lipsinHeader->addLinkToPreRoute(link);
    }
    packet->insertAtFront(lipsinHeader);
}
void IpvxTrafGen::encapsulateLipsin(Packet *packet)
{
    const auto& lipsinHeader = makeShared<LipsinHeader>();

    lipsinHeader->addLinkToPreRoute(1); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(33); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(74); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(72); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(114); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(112); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(154); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(152); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(194); // can add pre route link id into BF[0]
    lipsinHeader->addLinkToPreRoute(192); // can add pre route link id into BF[0]
    packet->insertAtFront(lipsinHeader);
    //preRoute(packet,61);
}
void IpvxTrafGen::encapsulateIpv4(Packet *transportPacket)
{
    const auto& ipv4Header = makeShared<Ipv4Header>();

    auto l3AddressReq = transportPacket->removeTag<L3AddressReq>();
    Ipv4Address src = l3AddressReq->getSrcAddress().toIpv4();
    bool nonLocalSrcAddress = l3AddressReq->getNonLocalSrcAddress();
    Ipv4Address dest = l3AddressReq->getDestAddress().toIpv4();
    delete l3AddressReq;

    ipv4Header->setProtocolId((IpProtocolId)ProtocolGroup::ipprotocol.getProtocolNumber(transportPacket->removeTagIfPresent<PacketProtocolTag>()->getProtocol()));

    auto hopLimitReq = transportPacket->removeTagIfPresent<HopLimitReq>();
    short ttl = (hopLimitReq != nullptr) ? hopLimitReq->getHopLimit() : -1;
    delete hopLimitReq;
    bool dontFragment = false;
    if (auto dontFragmentReq = transportPacket->removeTagIfPresent<FragmentationReq>()) {
        dontFragment = dontFragmentReq->getDontFragment();
        delete dontFragmentReq;
    }

    // set source and destination address
    ipv4Header->setDestAddress(dest);

    // set other fields
    if (TosReq *tosReq = transportPacket->removeTagIfPresent<TosReq>()) {
        ipv4Header->setTypeOfService(tosReq->getTos());
        delete tosReq;
        if (transportPacket->findTag<DscpReq>())
            throw cRuntimeError("TosReq and DscpReq found together");
        if (transportPacket->findTag<EcnReq>())
            throw cRuntimeError("TosReq and EcnReq found together");
    }
    if (DscpReq *dscpReq = transportPacket->removeTagIfPresent<DscpReq>()) {
        ipv4Header->setDscp(dscpReq->getDifferentiatedServicesCodePoint());
        delete dscpReq;
    }
    if (EcnReq *ecnReq = transportPacket->removeTagIfPresent<EcnReq>()) {
        ipv4Header->setEcn(ecnReq->getExplicitCongestionNotification());
        delete ecnReq;
    }

    ipv4Header->setIdentification(0);
    ipv4Header->setMoreFragments(false);
    ipv4Header->setDontFragment(dontFragment);
    ipv4Header->setFragmentOffset(0);

    if (ttl != -1) {
        ASSERT(ttl > 0);
    }
    else if (ipv4Header->getDestAddress().isLinkLocalMulticast())
        ttl = 1;
    else if (ipv4Header->getDestAddress().isMulticast())
        ttl = 64;
    else
        ttl = 64;
    ipv4Header->setTimeToLive(ttl);

    if (Ipv4OptionsReq *optReq = transportPacket->removeTagIfPresent<Ipv4OptionsReq>()) {
        for (size_t i = 0; i < optReq->getOptionArraySize(); i++) {
            auto opt = optReq->dropOption(i);
            ipv4Header->addOption(opt);
            ipv4Header->addChunkLength(B(opt->getLength()));
        }
        delete optReq;
    }

    ASSERT(ipv4Header->getChunkLength() <= IPv4_MAX_HEADER_LENGTH);
    ipv4Header->setHeaderLength(ipv4Header->getChunkLength());
    ipv4Header->setTotalLengthField(ipv4Header->getChunkLength() + transportPacket->getDataLength());
    transportPacket->insertAtFront(ipv4Header);
//    insertNetworkProtocolHeader(transportPacket, Protocol::ipv4, ipv4Header);
    // setting Ipv4 options is currently not supported

}

void IpvxTrafGen::printPacket(Packet *msg)
{
    L3Address src, dest;
    int protocol = -1;
    auto *ctrl = msg->getControlInfo();
    if (ctrl != nullptr) {
        protocol = ProtocolGroup::ipprotocol.getProtocolNumber(msg->getTag<PacketProtocolTag>()->getProtocol());
    }
    L3AddressTagBase *addresses = msg->findTag<L3AddressReq>();
    if (addresses == nullptr)
        addresses = msg->findTag<L3AddressInd>();
    if (addresses != nullptr) {
        src = addresses->getSrcAddress();
        dest = addresses->getDestAddress();
    }

    EV_INFO << msg << endl;
    EV_INFO << "Payload length: " << msg->getByteLength() << " bytes" << endl;

    if (protocol != -1)
        EV_INFO << "src: " << src << "  dest: " << dest << "  protocol=" << protocol << "\n";
}

void IpvxTrafGen::processPacket(Packet *msg)
{
    emit(packetReceivedSignal, msg);
    EV_INFO << "Received packet: ";
    printPacket(msg);
    delete msg;
    numReceived++;
}

void IpvxTrafGen::handleStartOperation(LifecycleOperation *operation)
{
    startApp();
}

void IpvxTrafGen::handleStopOperation(LifecycleOperation *operation)
{
    cancelNextPacket();
}

void IpvxTrafGen::handleCrashOperation(LifecycleOperation *operation)
{
    cancelNextPacket();
}

void ipvxTrafGenClearProtocols()
{
    for (auto *p: IpvxTrafGen::allocatedProtocols)
        delete p;
    IpvxTrafGen::allocatedProtocols.clear();
}

EXECUTE_ON_SHUTDOWN(ipvxTrafGenClearProtocols());

} // namespace inet

