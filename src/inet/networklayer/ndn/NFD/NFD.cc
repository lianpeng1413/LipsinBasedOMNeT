/*
 * NFD.cc
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#include "NFD.h"

#include <iostream>
#include <algorithm>

#include "inet/networklayer/contract/ndn/iData_m.h"
#include "inet/networklayer/contract/ndn/Interest_m.h"
#include "inet/networklayer/ndn/NFD/ndnAppData_m.h"
#include "inet/applications/common/SocketTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/networklayer/common/L3Tools.h"
#include "inet/networklayer/contract/ndn/ndnSocketCommand_m.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"

namespace inet
{

using std::string;
Define_Module(NFD);

void NFD::SimRecorder::ConsumerPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "sendNum: " << InterestSendNum << endl;
    os << "recvNum: " << DataRecvNum << endl;
    os << "recvSinglePktNum: " << owner->receiveMap.size() << endl;
    if (InterestSendNum != 0)
        os << "trans ratio: " << 100 * DataRecvNum / InterestSendNum << "%" << endl;
    os << "send Interval: " << owner->sendInterval << "s" << endl;
    os << "Throughput: " << DataRecvNum * 1000 * 8 / ((simTime().dbl() - owner->firstPacket.dbl()) * 1000 * 1000) << " Mbps" << endl;
    os << "Totol Throughput: " << totalThroughput.get() * 8 / ((simTime().dbl() - owner->firstPacket.dbl()) * 1000 * 1000) << " Mbps" << endl;
    os << "Average delay: ";
    double sum = 0;
    if(delayArrary.size()>0)
    {
        std::for_each(delayArrary.begin(), delayArrary.end(), [&sum](double value) { sum += value; });
        os << sum / delayArrary.size() << " ms" << endl;
    }
    else
        os << 0 << "ms" << endl;

    os << endl;
}

void NFD::SimRecorder::ProviderPrint(std::ostream &os)
{
    os << "index:    " << nodeName << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "InterestRecvNum: " << InterestRecvNum << endl;
    os << endl;
}

void NFD::SimRecorder::avtThroughputPrint(std::ostream &os)
{
    std::map<double, std::map<double, double>>::iterator iter;
    std::map<double, double>::iterator iters;

    for(iter = avgThoughputT.begin(); iter != avgThoughputT.end(); iter++)
    {
        for(iters = iter->second.begin(); iters != iter->second.end(); iters++)
        {
            os << "index:    " << nodeName << endl;
            os << "send Interval: " << owner->sendInterval << "s" << endl;
            os << "time: " << iter->first << endl;
            os << "current throughput: " << iters->first << " Mbps" << endl;
            os << "delay: " << iters->second << " ms" << endl;
            os << endl;
        }
    }
    os << endl;
}

NFD::~NFD()
{
//    finish();
}

void NFD::finish()
{
    record();
    ResemBuffer->flush();
    cancelAndDelete(avgThroughputTime);
    delete ResemBuffer;
}

void NFD::initialize(int stage)
{
    OperationalBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        nodeName = getParentModule()->getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node += str;
        nid.set("LEOSat", "orbit", node);

        ResemBuffer = new ndnFragBuf();
        // get forwarding table pointer
        auto name = getParentModule()->getParentModule()->getFullPath();
        name = name + ".interfaceTable";
        auto path = name.c_str();
        cModule *mod = this->getModuleByPath(path);
        ift = dynamic_cast<IInterfaceTable *>(mod);

        name = getParentModule()->getFullPath();
        name = name + ".fib";
        path = name.c_str();
        mod = this->getModuleByPath(path);
        rt = dynamic_cast<nlsr::Fib *>(mod);

        name = getParentModule()->getFullPath();
        name = name + ".cs";
        path = name.c_str();
        mod = this->getModuleByPath(path);
        ct = dynamic_cast<cacheTable *>(mod);

        name = getParentModule()->getFullPath();
        name = name + ".pit";
        path = name.c_str();
        mod = this->getModuleByPath(path);
        pit = dynamic_cast<pitBase *>(mod);

        mtu = par("mtu").intValue();
        hopLimit = par("hopLimit").intValue();
        routeLifeTime = par("routeLifeTime").doubleValue();

        testModule.owner = this;
        testModule.nodeName = getParentModule()->getParentModule()->getName();
        testModule.multiConsumer = par("multi").intValue();

        testModule.owner = this;
        testModule.multiConsumer = par("multi").intValue();
        syncInterval = par("syncInterval");
        sendInterval = par("sendInterval");
        RSpath=par("RSpath").stdstringValue();
        timeOut = 10;
        avgThroughputTime = new cMessage("avgThroughputTime");
        scheduleAt(simTime()+10, avgThroughputTime);

        registerService(Protocol::NFD, gate("transportIn"), gate("queueIn"));
        registerProtocol(Protocol::NFD, gate("queueOut"), gate("transportOut"));
    }
}

InterfaceEntry *NFD::chooseInterface(const char *interfaceName)
{
    InterfaceEntry *ie = nullptr;
    if (strlen(interfaceName) > 0)
    {
        ie = ift->findInterfaceByName(interfaceName);
        if (ie == nullptr)
            throw cRuntimeError("Interface \"%s\" does not exist", interfaceName);
    }
    else
    {
        // there should be exactly one non-loopback interface that we want to configure
        for (int i = 0; i < ift->getNumInterfaces(); i++)
        {
            InterfaceEntry *current = ift->getInterface(i);
            if (!current->isLoopback())
            {
                if (ie)
                    throw cRuntimeError("Multiple non-loopback interfaces found");
                ie = current;
            }
        }
        if (!ie)
            throw cRuntimeError("No non-loopback interface");
    }
    return ie;
}

void NFD::handleRegisterService(const Protocol &protocol, cGate *out, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterService");
}

void NFD::handleRegisterProtocol(const Protocol &protocol, cGate *in, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterProtocol");
    if (in->isName("transportIn"))
        upperProtocols.insert(&protocol);
}

void NFD::refreshDisplay() const
{
    OperationalBase::refreshDisplay();
}

void NFD::handleStartOperation(LifecycleOperation *operation)
{
    mtu = 1500;
    ct->setMtu(mtu);
}

void NFD::handleStopOperation(LifecycleOperation *operation)
{
}

void NFD::handleCrashOperation(LifecycleOperation *operation)
{
}

void NFD::handleMessageWhenUp(cMessage *msg)
{
    if (msg->arrivedOn("transportIn"))
    {
        if (auto request = dynamic_cast<Request *>(msg))
            handleRequest(request);
//        else
//            handlePacketFromHL(check_and_cast<Packet *>(msg));
    }

    else if (msg->arrivedOn("queueIn"))
    {
        EV_INFO << "Received " << msg << " from network.\n";
        handleIncomingDatagram(check_and_cast<Packet *>(msg));
    }
    else if (msg == avgThroughputTime)
    {
        double sum = 0;
        double delay = 0;
        double avgTh = 0;
        if(testModule.delayArrary.size()>0)
        {
            std::for_each(testModule.delayArrary.begin(), testModule.delayArrary.end(), [&sum](double value) { sum += value; });
            delay = sum / testModule.delayArrary.size();
        }
        avgTh = testModule.DataRecvNum * 1000 * 8 / ((simTime().dbl() - testModule.owner->firstPacket.dbl()) * 1000 * 1000);
        testModule.temp[avgTh] = delay;
        testModule.avgThoughputT[simTime().dbl()] = testModule.temp;
        scheduleAt(simTime()+10, avgThroughputTime);
    }
    else
        throw cRuntimeError("Message arrived on unknown gate '%s'", msg->getArrivalGate()->getName());
}

void NFD::handleIncomingDatagram(Packet *packet)
{
    //Get packet header, which from link layer
    const auto &head = packet->peekAtFront<Chunk>(B(128),0);
    auto pointer = head.get();

    Chunk *chunk = const_cast<Chunk *>(pointer);

    //Decide packet type through dynamic type transfer
    if (dynamic_cast<iData *>(chunk))
    {
        handleDataPacket(packet);
    }
    else if (dynamic_cast<Interest *>(chunk))
    {
        handleInterestPacket(packet);
    }
    else
    {
        throw cRuntimeError("unknow message type");
    }
}

void NFD::handleDataPacket(Packet *packet)
{
    packet->trim();

    const auto head = packet->peekAtFront<iData>();
    const iName &headInterest = head->getInterestName();
    auto offset = head->getOffset();
    auto localPort = head->getPortNumber2();
    auto sd = socketsByPortMap.find(localPort);

    bool flag = false;
    if(!ct->hasThisPacket(packet, headInterest)){ //caching received packet
        iName nodeNames;
        nodeNames.set("LEOSat", "orbit", nodeName);
        cacheDataFromLL(headInterest, packet, nodeNames);
    }
    else
        flag = true;

    if (sd != socketsByPortMap.end() && iNametoSockets.find(headInterest) != iNametoSockets.end())
    {
        if(receiveMap.find(headInterest) != receiveMap.end()){
            receiveMap[headInterest] += 1;
        }
        else {
            receiveMap[headInterest] = 1;
        }

        if(!flag)
            testModule.totalThroughput += B(packet->getByteLength()) - head->getChunkLength();

        auto fullPacket = ResemBuffer->addFragment(packet->dup(), simTime());
        if (fullPacket != nullptr)
        {
            decapsulate(fullPacket, headInterest);
            iNametoSockets.erase(headInterest);

            if(sd == socketsByPortMap.end())
            {
                throw cRuntimeError("No socket on that local port");
            }
            else
            {
                sendUp(fullPacket,sd->second, headInterest, localPort);
            }
        }
    }

    if (pit->haveThisInterest(headInterest))
    {
        //when received a data packet, search in pit, and send it to source interface.
        MacAddress nexthop;
        int nextInterface;

        auto range = pit->findPitEntry(headInterest);
        if(range.first != range.second){
            //modify packet header.
            packet->trim();
            const auto &newHead = packet->removeAtFront<iData>();
            packet->clearTags();
            newHead->setTimeToLive(newHead->getTimeToLive() - 1);
            newHead->setLastHop(nid);
            packet->insertAtFront(newHead);

            for (auto iter = range.first; iter != range.second; iter++)
            {
                packet->clearTags();
                nexthop = iter->second.getMac();
                nextInterface = iter->second.getInterfaceId();
                sendDatagramToOutput(packet,nextInterface, nexthop);
            }
            pit->removeEntry(headInterest);
    }}
    packet->trim();
    delete packet;
}

void NFD::handleInterestPacket(Packet *packet)
{
    packet->trim();
    auto macInfo = packet->getTag<MacAddressInd>();
    auto fromIE = getSourceInterface(packet);
    const auto &head = packet->removeAtFront<Interest>();

    auto headName = head->getInterestName();
    auto port = head->getPortNumber1();

    //First, search in cache table.
    if (findContentInCache(headName) == nullptr)
    {
        simtime_t ttl = 1;

        std::string tag, prefix, tail;
        iName interestN;
        tag = headName.getTag();
        prefix = headName.getPrefix();
        tail.append("1");
        interestN.set(tag, prefix, tail);

        auto route = rt->lookup(interestN); //TODO maybe has many nextHop??

        auto sourceNid = head->getSource();
        auto nonce = head->getNonce();
        auto mac = macInfo->getSrcAddress();

        if(!pit->haveThisInterest(headName))
        {
            if (route != nullptr)  // find in fib
            {
                const auto nextHop = route->getM_nexthopList().getNextHop();
                auto nextInterface = nextHop.getIfIndex();
                auto nextMac = nextHop.getNextMac();
                pit->createEntry(head->getInterestName(), head->getSource(), mac, simtime_t(4), fromIE->getInterfaceId(), head->getNonce()); //create pit.
                packet->clearTags();
                packet->insertAtFront(head);
                sendDatagramToOutput(packet,nextInterface,nextMac); //send out packet.
                packet->trim();
                delete packet;
            }
            else if (route == nullptr) // else broadCast interest.
            {
                pit->createEntry(head->getInterestName(), head->getSource(), mac, simtime_t(4), fromIE->getInterfaceId(), head->getNonce());
                packet->insertAtFront(head);
                for(int i = 0; i < ift->getNumInterfaces();i++)
                {
                    const InterfaceEntry *destIE = ift->getInterface(i);
                    if(!destIE->isLoopback() && destIE != fromIE && destIE->isUp())
                    {
                        packet->clearTags();
                        sendDatagramToOutput(packet, destIE->getInterfaceId(), MacAddress::BROADCAST_ADDRESS);
                    }
                }
                EV_INFO << "No route, broadcast the packet!"<< endl;
                packet->trim();
                delete packet;
            }
        }
        if(!pit->haveEntry(headName,head->getNonce()))
        {
            pit->createEntry(headName, sourceNid, mac, simtime_t(4), fromIE->getInterfaceId(), nonce);
        }
    }
    // cache hit. transmit packets which have cached.
    else
    {
        auto lists = findContentInCache(headName)->getList();

        for (const auto &P : lists)
        {
            if (P != nullptr) {
                interestIdentifier identifer(headName, head->getSource());
                if(interestTable.find(identifer) != interestTable.end()){
                    if(simTime() - interestTable[identifer] < 0.1)
                        break;
                }
                interestTable[identifer] = simTime();

                auto newP = P->dup();
                auto forwardHead = newP->removeAtFront<iData>();
                forwardHead->setPortNumber2(port);
                forwardHead->setLastHop(nid);

                newP->insertAtFront(forwardHead);
                newP->clearTags();
                sendDatagramToOutput(newP, fromIE->getInterfaceId(), macInfo->getSrcAddress());
                newP->trim();
                delete newP;
            }
        }
        packet->trim();
        delete packet;
    }
}

shared_ptr<inet::nlsr::FibEntry> NFD::findRoute(const iName& nid) //TODO
{
    return rt->lookup(nid);
}

void NFD::createPIT(const iName &interest, const iName &nid, const MacAddress &mac, simtime_t ttl, int interfaceId)
{
    pit->createEntry(interest, nid, mac, simtime_t(4), interfaceId);
}

pitBase::EntrysRange NFD::findPITentry(const iName& interest)
{
    return pit->findPitEntry(interest);
}

shared_ptr<contentBlock> NFD::findContentInCache(const iName &interest)
{
    return ct->getBlock(interest);
}

const Ptr<inet::Interest> NFD::InterestHead(const iName &interest)
{
    const auto &inter = makeShared<Interest>();
    inter->setInterestName(interest);
    inter->setType(1);  //interest packet
    inter->setHotCount(0);
    inter->setCanBePrefix(true);
    inter->setMustBeFresh(true);
    inter->setMTU(mtu);

    inter->setSource(nid);
    inter->setNonce(this->getRNG(0)->intRand());

    return inter;
}

const Ptr<inet::iData> NFD::DataHead(const iName &interest)
{
    const auto &data = makeShared<iData>();
    data->setInterestName(interest);
    data->setType(2);   //data packet
    data->setTimeToLive(60);
    data->setMTU(mtu);
    data->setLastHop(nid);
    data->setRouteMetric(1);

    return data;
}

void NFD::encapsulate(Packet *packet, int type, const iName& interest)
{
    if (type == 1) //Interest packet
    {
        auto inter = InterestHead(interest);
        packet->insertAtFront(inter);
    }
    if (type == 2) //data packet
    {
        auto data = DataHead(interest);
        data->setTotalLength(B(packet->getByteLength()));
        data->setComeFromSource(true);
        packet->insertAtFront(data);
    }
}

void NFD::encapsulate(Packet *packet, int type, const iName& interest, int port)
{
    if (type == 1) //Interest packet
    {
        auto inter = InterestHead(interest);
        inter->setPortNumber1(port);
        inter->setNonce(random());
        packet->insertAtFront(inter);
    }
    if (type == 2) //data packet
    {
        auto data = DataHead(interest);
        data->setTotalLength(B(packet->getByteLength()));
        data->setComeFromSource(true);
        data->setPortNumber2(port);
        packet->insertAtFront(data);
    }
}

void NFD::decapsulate(Packet *packet,  const iName& interest)
{
    testModule.DataRecvNum++;

    if(testModule.Delays.find(interest) == testModule.Delays.end())
        testModule.delayArrary.push_back(0);
    else
        testModule.delayArrary.push_back((simTime().dbl() - testModule.Delays[interest].dbl())*1000);

    testModule.Delays.erase(interest);

    testModule.goodThroughput += B(packet->getByteLength());
    packet->trim();
    packet->removeAtFront<iData>();
}

void NFD::sendDatagramToOutput(Packet *packet, int nic, const MacAddress &mac)
{
    EV_INFO << "Sending " << packet << " to output interface = " << nic << endl;

    packet->removeTagIfPresent<MacAddressReq>();
    auto macAddrReq = packet->addTag<MacAddressReq>();
    macAddrReq->setDestAddress(mac);

    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::NFD);
    packet->addTagIfAbsent<DispatchProtocolInd>()->setProtocol(&Protocol::NFD);

    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(nic);
    send(packet->dup(), "queueOut");
}

const InterfaceEntry *NFD::getSourceInterface(Packet *packet)
{
    auto tag = packet->findTag<InterfaceInd>();
    return tag != nullptr ? ift->getInterfaceById(tag->getInterfaceId()) : nullptr;
}

void NFD::sendInterest(const iName &interest, int port) //send interest which from local.
{
    Packet *packet = new Packet("Interest");

    encapsulate(packet, 1, interest, port);

    std::string tag, prefix, tail;
    iName interestN;
    tag = interest.getTag();
    prefix = interest.getPrefix();
    tail.append("1");
    interestN.set(tag, prefix, tail);

    auto route = rt->lookup(interestN);

    if(route != nullptr) // has route, send interest to nextHop through interface
    {
        const auto nextHop = route->getM_nexthopList().getNextHop();
        auto nextInterface = nextHop.getIfIndex();
        auto nextMac = nextHop.getNextMac();
        packet->clearTags();
        sendDatagramToOutput(packet,nextInterface,nextMac); //send out packet.
        packet->trim();
        delete packet;
    }

    else if (route == nullptr) {// else broadCast interest.
        for(int i = 0; i < ift->getNumInterfaces();i++)
        {
            const InterfaceEntry *destIE = ift->getInterface(i);
            if(!destIE->isLoopback() && destIE->isUp())
            {
                packet->clearTags();
                sendDatagramToOutput(packet, destIE->getInterfaceId(),MacAddress::BROADCAST_ADDRESS);
            }
        }
        packet->trim();
        delete packet;
    }
}

void NFD::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
}

void  NFD::handleRequest(Request *request)
{
    auto ctrl = request->getControlInfo();
    if (ctrl == nullptr){
        throw cRuntimeError("Request '%s' arrived without controlinfo", request->getName());
        delete request;
    }
    else if(ndnSocketBindCommand *command = dynamic_cast<ndnSocketBindCommand *>(ctrl))
    {
        int socketId = request->getTag<SocketReq>()->getSocketId();
        SocketDescriptor *descriptor = new SocketDescriptor(socketId, command->getProtocol()->getId(), command->getNid(),command->getLocalPort());
        socketsByPortMap[command->getLocalPort()] = descriptor;
        socketIdToSocketDescriptor[socketId] = descriptor;
        delete request;
    }

    else if(ndnSocketSendInterestCommand *command = dynamic_cast<ndnSocketSendInterestCommand *>(ctrl))
    {
        if(firstPacket < 1){
            firstPacket = simTime().dbl();
        }

        auto interestName = command->getInterest();
        auto port = command->getLocalPort();
        CnodeName = nodeName; //set this node as requester name.

        sendInterval = command->getInter();
        testModule.InterestSendNum++;
        testModule.Delays[interestName] = simTime();

        iNametoSockets[interestName] = command->getLocalPort();

        //search this name in cache
        auto block = findContentInCache(interestName);
        if(block != nullptr){
            auto pktList = block->getList();
            Packet *fullPacket;
            for (auto iter = pktList.begin(); iter != pktList.end(); iter++)
            {
                fullPacket = ResemBuffer->addFragment((*iter)->dup(), simTime());

                testModule.totalThroughput += B((*iter)->getByteLength()) - B(78);
                if (nodeName == CnodeName)
                {
                    testModule.tempThput += (*iter)->getByteLength() * 8;
                }
            }

            if (fullPacket != nullptr)
            {
                auto sd = socketsByPortMap.find(port);
                decapsulate(fullPacket, interestName);
                iNametoSockets.erase(interestName);

                if (sd == socketsByPortMap.end())
                {
                    throw cRuntimeError("No socket on that local port");
                }
                else
                {
                    sendUp(fullPacket, sd->second, interestName, port);
                }
                return;
            }
            else
            {
                std::cout << nodeIndex << " incomplete local cache " << simTime() << " " << endl;
            }
        }
        else
            sendInterest(command->getInterest(), command->getLocalPort());
        if(iNametoSockets.size()==0)
            firstPacket = simTime();

        delete request;
    }
    else if(ndnSocketCacheDataCommand *command = dynamic_cast<ndnSocketCacheDataCommand *>(ctrl))
    {
        PnodeName = nodeName;
        auto msg = const_cast<cMessage *>(command->getPkt());
        auto pkt = dynamic_cast<Packet *>(msg);

        iName serviceName, nodeNames;
        serviceName = command->getInterest();
        nodeNames.set("LEOSat", "orbit", nodeName);
        cacheDataFromHL(serviceName, pkt, nodeNames);
        delete request;
    }
}

void NFD::cacheDataFromHL(const iName &interest, Packet* packet, iName & originRouter)
{
    const auto &data = makeShared<iData>();
    int headerLength = data->getHeaderLength().get();
    int payloadLength = packet->getByteLength();
    int fragmentLength = ((mtu - headerLength) / 8) * 8;
    ASSERT(fragmentLength > 0);

    if (headerLength + payloadLength < mtu)
    {
        encapsulate(packet, 2, interest);
        const auto &testhead = packet->peekAtFront<Chunk>(B(128), 0);
        ct->cachePacketFromHL(interest, packet->dup(), originRouter);
    }
    else
    {
        string fragMsgName = packet->getName();
        fragMsgName += "-frag-";

        for (int offset = 0; offset < payloadLength;)
        {
            bool lastFragment = (offset + fragmentLength >= payloadLength);

            int thisFragmentLength = lastFragment ? payloadLength - offset : fragmentLength;

            string curFragName = fragMsgName + std::to_string(offset);
            if (lastFragment)
                curFragName += "-last";
            Packet *fragment = new Packet(curFragName.c_str());

            ASSERT(fragment->getByteLength() == 0);
            auto fraghdr = staticPtrCast<iData>(data->dupShared());
            const auto &fragData = packet->peekDataAt(B(offset), B(thisFragmentLength));
            ASSERT(fragData->getChunkLength() == B(thisFragmentLength));
            fragment->insertAtBack(fragData);

            auto head = DataHead(interest);
            if (!lastFragment)
                head->setMoreFragments(true);

            head->setOffset(offset);
            head->setTotalLength(B(headerLength + thisFragmentLength));
            fragment->insertAtFront(head);
            ct->cachePacketFromHL(interest, fragment, originRouter);
            offset += thisFragmentLength;
        }
    }
    packet->trim();
    delete packet;
}


std::shared_ptr<contentBlock> NFD::cacheDataFromLL(const iName &interest, Packet* packet, iName & originRouter)
{
    packet->trim();
    auto newPacket = packet->dup();
    const auto &CacheHead = newPacket->removeAtFront<iData>();
    CacheHead->setTimeToLive(8);
    CacheHead->setComeFromSource(false);
    CacheHead->setRouteMetric(1);

    auto block = findContentInCache(interest);
    if (block == nullptr)
    {
        block = ct->createBlock(interest, 4);
    }
    newPacket->insertAtFront(CacheHead);
    block->insterPacket(newPacket);
    return block;
}

//For ndn file transport test.
void NFD::sendUp(Packet *packet, SocketDescriptor *sd, const iName &interest, double port)
{
    //For ndn file transport test.
//    packet->removeTagIfPresent<DispatchProtocolReq>();
//
//    Packet *pkt = new Packet("dataSendUp");
//    encapsulate(pkt, 2, interest, port);
//
//    long len = 1000;
//    const auto& payload = makeShared<ByteCountChunk>(B(len));
//    pkt->insertAtBack(payload);
//
//    pkt->removeTagIfPresent<DispatchProtocolReq>();
//    pkt->addTagIfAbsent<SocketInd>()->setSocketId(sd->socketId);
//    send(pkt,"transportOut");
//    delete packet;

    //For ndn request-response transport test.
//    packet->removeTagIfPresent<DispatchProtocolReq>();
//    packet->addTagIfAbsent<SocketInd>()->setSocketId(sd->socketId);
//    send(packet,"transportOut");
    delete packet;
}

void NFD::record()
{
    std::ofstream outfile;
    if (nodeName == CnodeName)
    {
        auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() +
                string("_") + std::to_string(this->getSyncInterval()) + string("_") + string("_ConsumeNetw.txt");
        outfile.open(RSpath + fileName, std::ofstream::app);
        testModule.ConsumerPrint(outfile);
        outfile.close();
//
//        std::ofstream outfile2;
//        auto fileName2 = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() +
//                string("_") + std::to_string(this->getSyncInterval()) + string("_") + std::to_string(this->getSendInterval()) + string("_avgThougput.txt");
//        outfile2.open("./simu/" + fileName2, std::ofstream::app);
//        testModule.avtThroughputPrint(outfile2);
//        outfile2.close();
    }
}

} // namespace inet


