/*
 * ndnFlood.cc
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#include "ndnFlood.h"

#include <iostream>
#include <algorithm>

#include "inet/networklayer/ndn/NFD/ndnAppData_m.h"
#include "inet/networklayer/contract/ndn/iData_m.h"
#include "inet/networklayer/contract/ndn/Interest_m.h"
#include "inet/applications/common/SocketTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/networklayer/common/L3Tools.h"
#include "inet/networklayer/contract/ndn/ndnSocketCommand_m.h"

namespace inet
{

using std::string;
Define_Module(ndnFlood);

void ndnFlood::SimRecorder::ConsumerPrint(std::ostream &os)
{

    os << "index:    " << index << endl;
    os << "sendNum: " << InterestSendNum << endl;
    os << "recvNum: " << DataRecvNum << endl;
    if (InterestSendNum != 0)
        os << "trans ratio: " << 100 * DataRecvNum / InterestSendNum << "%" << endl;
    os << "send Interval: " << owner->sendInterval << "s" << endl;
    os << "Throughput: " << throughput.get() * 8 / ((simTime().dbl() - owner->firstPacket.dbl()) * 1000 * 1000) << " Mbps" << endl;
    os << "Average delay: ";
    double sum = 0;
//    if(delayArray.size()>0)
//    {
//        std::for_each(delayArray.begin(), delayArray.end(), [&sum](double value) { sum += value; });
//        os << sum / delayArray.size() << " ms" << endl;
////    }
//    else
//        os << 0 << "ms" << endl;

    os << endl;
}

void ndnFlood::SimRecorder::ProviderPrint(std::ostream &os)
{
    os << "index:    " << index << endl;
    os << "DataSendNum: " << DataSendNum << endl;
    os << "InterestRecvNum: " << InterestRecvNum << endl;
    os << endl;
}

ndnFlood::~ndnFlood()
{
}

void ndnFlood::finish()
{
    record();
    cancelAndDelete(testInterest);
    cancelAndDelete(testData);
}

void ndnFlood::initialize(int stage)
{
    OperationalBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
    {
        nodeIndex = getParentModule()->getParentModule()->getIndex();
        nodeName = getParentModule()->getParentModule()->getName();
        std::string str(nodeName);
        std::string node;
        node += str;
        nid.set("LEOSat", "orbit", node);

        //TODO
        testTimer = nullptr;
        testInterest = new cMessage("testInterest");
        testData = new cMessage("testData");

        testinterest = 2 + 1.0 / (nodeIndex % 10 + 1);
        testdata = 1;

        testModule.owner = this;
        testModule.index = nodeIndex;
        testModule.multiConsumer = par("multi").intValue();


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
        rt = dynamic_cast<fibBase *>(mod);

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

        TC = par("TC").intValue();

        flood = par("flood").boolValue();
        unicast = par("unicast").boolValue();
        routeLifeTime = par("routeLifeTime").doubleValue();

        registerService(Protocol::NFD, gate("transportIn"), gate("queueIn"));
        registerProtocol(Protocol::NFD, gate("queueOut"), gate("transportOut"));
    }
}

InterfaceEntry *ndnFlood::chooseInterface(const char *interfaceName)
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

void ndnFlood::handleRegisterService(const Protocol &protocol, cGate *out, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterService");
}

void ndnFlood::handleRegisterProtocol(const Protocol &protocol, cGate *in, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterProtocol");
    if (in->isName("transportIn"))
        upperProtocols.insert(&protocol);
}

void ndnFlood::refreshDisplay() const
{
    OperationalBase::refreshDisplay();
}

void ndnFlood::start()
{
}

void ndnFlood::handleStartOperation(LifecycleOperation *operation)
{
    start();

    if (testModule.multiConsumer == 1)
    {
        if (nodeIndex % Cindex == 0)
            scheduleAt(testinterest, testInterest);

    }
    else if (testModule.multiConsumer == 0)
    {
        if (nodeIndex == Cindex)
            scheduleAt(testinterest, testInterest);

    }
    else if (testModule.multiConsumer == 2)
    {
        // std::cout << "sch" << endl;
        if (nodeIndex - Cindex >= 0 && nodeIndex - Cindex <= 3)
        {
            scheduleAt(testinterest, testInterest);
        }

    }
}

void ndnFlood::handleStopOperation(LifecycleOperation *operation)
{
    // TODO: stop should send and wait pending packets
    cancelAndDelete(testInterest);
    cancelAndDelete(testData);
}

void ndnFlood::handleCrashOperation(LifecycleOperation *operation)
{
    cancelAndDelete(testInterest);
    cancelAndDelete(testData);
}

void ndnFlood::handleMessageWhenUp(cMessage *msg)
{
    if (msg->arrivedOn("transportIn"))
    {
        if (auto request = dynamic_cast<Request *>(msg))
            handleRequest(request);
        else handlePacketFromHL(check_and_cast<Packet *>(msg));
    }

    else if (msg->arrivedOn("queueIn"))
    {
        EV_INFO << "Received " << msg << " from network.\n";
        handleIncomingDatagram(check_and_cast<Packet *>(msg));
    }

    else
        throw cRuntimeError("Message arrived on unknown gate '%s'", msg->getArrivalGate()->getName());
}

void ndnFlood::handleIncomingDatagram(Packet *packet)
{
    const auto &head = packet->peekAtFront<Chunk>(B(128),0);
    auto pointer = head.get();

    Chunk *chunk = const_cast<Chunk *>(pointer);

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

void ndnFlood::handleDataPacket(Packet *packet)
{
    const auto head = packet->peekAtFront<iData>();
    const iName &headInterest = head->getInterestName();
    auto localPort = head->getPortNumber2();
    auto sd = socketsByPortMap.find(localPort);

    auto newPacket = packet->dup();

    if (sd != socketsByPortMap.end() && iNametoSockets.find(headInterest) != iNametoSockets.end())
    {
        std::cout << "one packet received" << endl;
        std::cout << "off set is " << head->getOffset() << endl;

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
                sendUp(fullPacket,sd->second);
            }

        }
    }

    // search pit: maybe there's many item.
    if (pit->haveThisInterest(headInterest))
    {
         std::cout << "Data received, PIT hit. " << " at " << simTime() << endl;

         //when received a data packet, search in pit, and send it to source interface.
        MacAddress nexthop;
        int nextInterface;

        auto range = findPITentry(headInterest);

        for (auto iter = range.first; iter != range.second; iter++)
        {
            nexthop = iter->second.getMac();
            nextInterface = iter->second.getInterfaceId();

            if (!ct->hasThisPacket(packet, headInterest))
            {
                std::cout << "Data received: " << getParentModule()->getParentModule()->getIndex() << endl;

                if (head->getTotalLength() < newPacket->getDataLength())
                {
                    newPacket->setBackOffset(newPacket->getFrontOffset() + head->getTotalLength());
                }
                newPacket->trim();
                const auto &newHead = newPacket->removeAtFront<iData>();

                auto CacheHead = makeShared<iData>(*newHead->dup());
                CacheHead->setTimeToLive(8);
                CacheHead->setComeFromSource(false);
                CacheHead->setRouteMetric(0);

                newPacket->clearTags();
                newHead->setTimeToLive(newHead->getTimeToLive() - 1);
                newHead->setLastHop(nid);
                auto metric = newHead->getRouteMetric();
                if(metric != 0)
                    newHead->setRouteMetric(metric - 1);

                auto CachePacket = newPacket->dup();
                CachePacket->insertAtFront(CacheHead);

                newPacket->insertAtFront(newHead);

                auto block = findContentInCache(headInterest);
                if (block == nullptr)
                {
                    block = ct->createBlock(headInterest, 10);
                }
                block->insterPacket(CachePacket);

                sendDatagramToOutput(newPacket->dup(),nextInterface, nexthop);//TODO
            }
        }
        pit->removeEntry(headInterest);
    }
    else
    {
    }
    delete packet;
    delete newPacket;
}

void ndnFlood::handleInterestPacket(Packet *packet)
{
    packet->trim();

    auto macInfo = packet->getTag<MacAddressInd>();
    auto fromIE = getSourceInterface(packet);
    const auto &head = packet->removeAtFront<Interest>();

    auto headName = head->getInterestName();
    auto port = head->getPortNumber1();

    std::cout << " Received interest name: " << headName << endl;
    auto route = rt->findRoute(headName);  //TODO Find out forwarding table.

    //First, search in cache table.
    if (findContentInCache(headName) == nullptr)
    {
        simtime_t ttl = 1;
        auto route = rt->findRoute(headName); //TODO maybe has many nextHop??

        auto sourceNid = head->getSource();
        auto nonce = head->getNonce();
        auto mac = macInfo->getSrcAddress();

        if(!pit->haveThisInterest(headName))
        {
            if (route != nullptr)  // find in fib
            {
                auto nextInterface = route->getInterFace();
                pit->createEntry(head->getInterestName(), head->getSource(), mac, ttl, fromIE->getInterfaceId(), head->getNonce());

                packet->clearTags();

                head->setMAC(myMacAddress);
                packet->insertAtFront(head);

                sendDatagramToOutput(packet->dup(),nextInterface);
            }
            else if (route == nullptr) // else broadCast interest.
            {
                pit->createEntry(head->getInterestName(), head->getSource(), mac, ttl, fromIE->getInterfaceId(), head->getNonce());

                Packet *newPacket = packet->dup();
                newPacket->clearTags();
                newPacket->insertAtFront(head);

                for(int i = 0; i < ift->getNumInterfaces();i++)
                {
                    const InterfaceEntry *destIE = ift->getInterface(i);
                    if(!destIE->isLoopback() && destIE != fromIE && destIE->isUp())
                    {
                        sendDatagramToOutput(newPacket, destIE->getInterfaceId(), macInfo->getDestAddress());
                    }
                }

                delete newPacket;
            }
        }
        if(!pit->haveEntry(headName,head->getNonce()))
        {
            pit->createEntry(headName, sourceNid, mac,simtime_t(1), fromIE->getInterfaceId(), nonce);
        }

    }
    // cache hit. transmit packets which have cached.
    else
    {
        std::cout << " Content Found! " << " at " << simTime() << endl;

        auto lists = findContentInCache(headName)->getList();

        for (const auto &P : lists)
        {
            if (P != nullptr)
            {
                interestIdentifier identifer(headName, head->getSource());
                if(interestTable.find(identifer) != interestTable.end()){
                    if(simTime() - interestTable[identifer] < 0.1)
                        break;
                }
                interestTable[identifer] = simTime();

                testModule.DataSendNum++;

                auto newP = P->dup();

                auto forwardHead = newP->removeAtFront<iData>();
                forwardHead->setPortNumber2(port);
                forwardHead->setLastHop(nid);

                newP->insertAtFront(forwardHead);

                sendDatagramToOutput(newP, fromIE->getInterfaceId(), macInfo->getSrcAddress());

            }
        }
    }

    delete packet;
}

shared_ptr<iFib> ndnFlood::findRoute(const iName& nid) //TODO
{
    return rt->findRoute(nid);
}

void ndnFlood::createPIT(const iName &interest, const iName &nid, const MacAddress &mac, simtime_t ttl, int interfaceId)
{
    pit->createEntry(interest, nid, mac, ttl, interfaceId);
}

pitBase::EntrysRange ndnFlood::findPITentry(const iName& interest)
{
    return pit->findPitEntry(interest);
}

void ndnFlood::cachePacket(const iName &interest, Packet *packet, iName & originRouter)
{
    ct->cachePacket(interest, packet, originRouter);
}

shared_ptr<contentBlock> ndnFlood::findContentInCache(const iName &interest)
{
    return ct->getBlock(interest);
}

const Ptr<inet::Interest> ndnFlood::InterestHead(const iName &interest)
{
    const auto &inter = makeShared<Interest>();
    inter->setInterestName(interest);
    inter->setType(1);  //interest packet
    inter->setHotCount(0);
    inter->setCanBePrefix(true);
    inter->setMustBeFresh(true);
    inter->setMTU(mtu);

    inter->setSource(nid);
    inter->setMAC(myMacAddress);
    inter->setNonce(this->getRNG(0)->intRand());

    return inter;
}

const Ptr<inet::iData> ndnFlood::DataHead(const iName &interest)
{
    const auto &data = makeShared<iData>();
    data->setInterestName(interest);
    data->setType(2);   //data packet
    data->setTimeToLive(hopLimit);
    data->setMTU(mtu);
    data->setLastHop(nid);
    data->setMAC(myMacAddress);

    return data;
}

void ndnFlood::encapsulate(Packet *packet, int type, const iName& interest)
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

void ndnFlood::encapsulate(Packet *packet, int type, const iName& interest, int port)
{
    if (type == 1) //Interest packet
    {
        auto inter = InterestHead(interest);
        inter->setPortNumber1(port);
        inter->setNonce(std::rand());

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

void ndnFlood::decapsulate(Packet *packet,  const iName& interest)
{

    testModule.DataRecvNum++;

    testModule.Delays.erase(interest);

    testModule.throughput += B(packet->getByteLength());
    packet->trim();
    packet->removeAtFront<iData>();
}

void ndnFlood::sendDatagramToOutput(Packet *packet, int nic, const MacAddress &mac)
{
    EV_INFO << "Sending " << packet << " to output interface = "
            << "ie" << endl;

    packet->removeTagIfPresent<MacAddressReq>();
    auto macAddrReq = packet->addTag<MacAddressReq>();
    macAddrReq->setSrcAddress(myMacAddress);
    macAddrReq->setDestAddress(mac);

    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::NFD);
    packet->addTagIfAbsent<DispatchProtocolInd>()->setProtocol(&Protocol::NFD);

    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(nic);

    send(packet->dup(), "queueOut");
}

void ndnFlood::handlePacketFromHL(Packet *packet)
{
    //TODO recommend rewrite like IPV4
}

const InterfaceEntry *ndnFlood::getSourceInterface(Packet *packet)
{
    auto tag = packet->findTag<InterfaceInd>();
    return tag != nullptr ? ift->getInterfaceById(tag->getInterfaceId()) : nullptr;
}

void ndnFlood::fragmentAndStore(Packet *packet, const iName &interest, iName & originRouter)
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
        cachePacket(interest, packet->dup(), originRouter);
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
//            head->getTraceForUpdate().push_back(getParentModule()->getParentModule()->getIndex());

            fragment->insertAtFront(head);

            //            auto datalen = fragment->getDataLength().get();

            cachePacket(interest, fragment, originRouter);
            offset += thisFragmentLength;
        }

    }
    delete packet;
}

void ndnFlood::fragmentAndSend(Packet *packet)
{
}

void ndnFlood::sendInterest(const iName &interest, int port) //send interest which from local.
{
    Packet *packet = new Packet("Interest");

    encapsulate(packet, 1, interest, port);

    auto route = rt->findRoute(interest);


    if(route != nullptr) // has route, send interest to nextHop through interface
    {
        Packet  *newPacket = packet->dup();
        sendDatagramToOutput(newPacket, route->getInterFace(), route->getNextMac());

    }

    else{ //no interface, broadcast.
        for(int i = 0; i < ift->getNumInterfaces();i++)
        {
            const InterfaceEntry *destIE = ift->getInterface(i);
            if(!destIE->isLoopback() && destIE->isUp())
            {
                Packet  *newPacket = packet->dup();
                sendDatagramToOutput(newPacket, destIE->getInterfaceId(),MacAddress::BROADCAST_ADDRESS);
            }
        }
    }
    testModule.Delays[interest] = simTime();
    testModule.InterestSendNum++;
}

void ndnFlood::testProvide(const iName &interest, const B &dataSize)
{
    auto playload = makeShared<ndnAppData>();
    playload->setChunkLength(dataSize);
    Packet *packet = new Packet("DATA");

    packet->insertAtBack(playload);
    std::cout<< "cached data: " << interest.str()<<endl;
    iName nodeNames;
    nodeNames.set("LEOSat", "orbit", nodeName);
    fragmentAndStore(packet, interest, nodeNames);
}
void ndnFlood::cacheData(const iName &interest, Packet *packet, iName & originRouter)
{
    fragmentAndStore(packet, interest, originRouter);
}

void ndnFlood::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
}

void ndnFlood::record()
{
    std::ofstream outfile;

    if (nodeIndex == Cindex)
    {
        auto fileName = cSimulation::getActiveEnvir()->getConfigEx()->getActiveConfigName() + string("_Consume10r.txt");
        outfile.open("./simu/" + fileName, std::ofstream::app);
        testModule.ConsumerPrint(outfile);
        outfile.close();
    }

}

void  ndnFlood::handleRequest(Request *request)
{
//    auto node = this->getParentModule()->getFullPath();
//    std::cout<<node<<endl;
    auto ctrl = request->getControlInfo();
    if (ctrl == nullptr)
        throw cRuntimeError("Request '%s' arrived without controlinfo", request->getName());
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
        Cindex = nodeIndex;
        sendInterval = command->getInter();
        sendInterest(command->getInterest(), command->getLocalPort());
        if(iNametoSockets.size()==0)
            firstPacket = simTime();
        iNametoSockets[command->getInterest()] = command->getLocalPort();
        delete request;
    }
    else if(ndnSocketCacheDataCommand *command = dynamic_cast<ndnSocketCacheDataCommand *>(ctrl))
    {
        Pindex = nodeIndex;
        auto msg = const_cast<cMessage *>(command->getPkt());
        auto pkt = dynamic_cast<Packet *>(msg);

        iName serviceName, nodeNames;
        serviceName = command->getInterest();
        nodeNames.set("LEOSat", "orbit", nodeName);

        cacheData(serviceName, pkt, nodeNames);
        delete request;
    }
}

void ndnFlood::sendUp(Packet *pkt, SocketDescriptor *sd)
{
    pkt->removeTagIfPresent<DispatchProtocolReq>();
    pkt->addTagIfAbsent<SocketInd>()->setSocketId(sd->socketId);
    send(pkt,"transportOut");
}

INetfilter::IHook::Result ndnFlood::datagramPreRoutingHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result ndnFlood::datagramForwardHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result ndnFlood::datagramPostRoutingHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result ndnFlood::datagramLocalInHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}


INetfilter::IHook::Result ndnFlood::datagramLocalOutHook(Packet *datagram)
{
    return INetfilter::IHook::ACCEPT;
}

void ndnFlood::registerHook(int priority, IHook *hook)
{

}


void ndnFlood::unregisterHook(IHook *hook)
{

}


void ndnFlood::dropQueuedDatagram(const Packet *datagram)
{

}


void ndnFlood::reinjectQueuedDatagram(const Packet *datagram)
{

}

} // namespace inet


