/*
 * HelloHandler.cc
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/messageHandler/HelloHandler.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/Nlsr.h"

namespace inet {
namespace nlsr {

HelloHandler::HelloHandler(Router *containingRouter) : IMessageHandler(containingRouter)
{
}

void HelloHandler::processInterestPacket(Packet *packet, NlsrInterface *intf, Neighbor *unused)
{
    int interfaceId = packet->getTag<InterfaceInd>()->getInterfaceId();
    const auto& helloInterestPacket = packet->peekAtFront<NlsrHelloInterest>();

    if((intf->getHelloInterval() == helloInterestPacket->getHelloInterval()) &&
       (intf->getRouterDeadInterval() == helloInterestPacket->getRouterDeadInterval()) &&
       (helloInterestPacket->getHopLimit() == 1) && helloInterestPacket->getHopCount() == 0)
    {
        // interest name: /<neighbor>/HELLOINFO/<localRouter>
        iName helloInterestName = helloInterestPacket->getInterestName();

        std::string neighborName = "/";
        neighborName += helloInterestName.getTail();  //Get neighbor name
        EV_INFO << this->router->getRouterID().str() << " Receive Hello Interest name: " << helloInterestName.str() << "  from neighbor: " << neighborName << endl;

        //Get local router name
        iName localRouter = router->getRouterID();

        Packet *dataPacket = new Packet("data");

        const auto& data = makeShared<NlsrHelloData>(); //Create hello data header
        iName interestName;
        interestName.set(neighborName.erase(0, 1), "HelloINFO", localRouter.str().erase(0, 1));//get this router name

        data->setInterestName(interestName);
        data->setHopCount(0);
        data->setSeqNo(0);
        data->setType(HELLO_DATA);
        data->setVersion(2);
        data->setHopLimit(1);
        data->setRouterDeadInterval(helloInterestPacket->getRouterDeadInterval());

        dataPacket->insertAtFront(data);

        iName neighborN;
        neighborN.transName(neighborName);
        EV_INFO << "Sending out hello data with name: " << interestName.str() << endl;

        //Add neighbor info.
        Neighbor *neighbor;
        neighbor = intf->getArea()->getRouter()->getAdjacencyList()->getNeighbor(neighborN);

        if(neighbor != nullptr)
        {// Has this neighbor, do nothing, just print event.
            router->getMessageHandler()->printEvent("Hello data packet received", intf, neighbor);
        }

        //Create neighbor and add it to neighbor list. Then change neighbor state.
        else{
            EV_INFO << this->router->getRouterID().str() << " Create neighbor " << neighborN.str()<< " and add it to neighbor list." << endl;
            neighbor = new Neighbor(neighborN); //Create neighbor
            neighbor->setNeighborName(neighborN);
            neighbor->setInterface(intf);
            neighbor->getInterface()->setNeighborMac(intf->getNeighborMac());
            neighbor->getInterface()->setOutputCost(1);
            neighbor->getInterface()->setIfToNeighbor(interfaceId);
            neighbor->setSyncHandler(router->getMessageHandler()->getSyncHandler());
            neighbor->setSyncInterval(router->getSyncInterval());
            neighbor->setRouterDeadInterval(helloInterestPacket->getRouterDeadInterval());
            intf->addNeighbor(neighbor); // add neighbor to interface
            router->getAdjacencyList()->insert(neighbor);

            iName adjLsaName; // Create adjLsa name
            adjLsaName.set(router->getRouterID().str().erase(0, 1), "ADJLSA", std::to_string(0));
            generateAdjLsaAndInstall(adjLsaName, intf);
            neighbor->processEvent(Neighbor::HELLO_DATA_RECEIVED);
        }

        MessageHandler *messageHandler = router->getMessageHandler();
        messageHandler->sendPacket(dataPacket, neighborN, intf, 1);
        dataPacket->trim();
        delete dataPacket;
    }
}

  // This checks Hello data and install into LSDB.
void HelloHandler::processDataPacket(Packet *dataPacket, NlsrInterface *intf)
{
    int interfaceId = dataPacket->getTag<InterfaceInd>()->getInterfaceId();

    const auto& helloData = dataPacket->peekAtFront<NlsrHelloData>();
    iName dataName = helloData->getInterestName();
    EV_INFO << "Received hello data for name: " << dataName.str() << endl;

    // interest name: /<neighbor>/HELLOINFO/<router>
    std::string neighborRouterName = dataName.getTail();  //Get neighbor name
    EV_INFO << "Hello data packet from neighbor: " << neighborRouterName << endl;

    iName neighborRouter;
    neighborRouter.transName(neighborRouterName); //neighboring router name

    if((helloData->getHopLimit() == 1) && helloData->getHopCount() == 0)
    {
        Neighbor *neighbor;
        neighbor = intf->getArea()->getRouter()->getAdjacencyList()->getNeighbor(neighborRouter);
        if(neighbor != nullptr)
        {// Has this neighbor, do nothing, just print event.
            router->getMessageHandler()->printEvent("Hello data packet received", intf, neighbor);
            neighbor->processEvent(Neighbor::HELLO_DATA_RECEIVED);
        }

        //Create neighbor and add it to neighbor list. Then change neighbor state.
        else{
            neighbor = new Neighbor(neighborRouter); //Create neighbor
            neighbor->setNeighborName(neighborRouter);
            neighbor->setInterface(intf);
            neighbor->getInterface()->setNeighborMac(intf->getNeighborMac());
            neighbor->getInterface()->setOutputCost(1);
            neighbor->getInterface()->setIfToNeighbor(interfaceId);
            neighbor->setSyncHandler(router->getMessageHandler()->getSyncHandler());
            neighbor->setSyncInterval(router->getSyncInterval());
            neighbor->setRouterDeadInterval(helloData->getRouterDeadInterval());
            intf->addNeighbor(neighbor); // add neighbor to interface
            router->getAdjacencyList()->insert(neighbor);

            iName adjLsaName, routerName; // Create adjLsa name
            routerName = router->getRouterID();
            adjLsaName.set(routerName.str().erase(0, 1), "ADJLSA", std::to_string(0));
            generateAdjLsaAndInstall(adjLsaName, intf);
            neighbor->processEvent(Neighbor::HELLO_DATA_RECEIVED);
        }
//        neighbor->processEvent(Neighbor::HELLO_DATA_RECEIVED);
    }
}

void HelloHandler::generateAdjLsaAndInstall(iName adjLsaName, NlsrInterface *intf)
{
    /* Generate adjLSA and install it into adjLSDB.
     * adjLSA name: /localRouter/ADJLSA/version.*/
    EV_INFO << "Create adjLSA:' " << adjLsaName.str()<< " ' and install it to LSDB." << endl;
    iName localRouter = router->getRouterID();

    NlsrAdjLsa *adjLsa = intf->getArea()->findAdjLsa(adjLsaName);
    if(adjLsa == nullptr) {
        NlsrAdjLsa *newAdjLSA = new NlsrAdjLsa;
        NlsrLsaHeader& lsaHeader = newAdjLSA->getHeaderForUpdate();

        lsaHeader.setLsAge(0);
        lsaHeader.setInterestName(adjLsaName);
        lsaHeader.setLsType(ADJ_LSA);
        lsaHeader.setHopCount(0);
        lsaHeader.setSeqNo(0);
        lsaHeader.setHopLimit(1);
        lsaHeader.setOriginRouter(localRouter);
        lsaHeader.setLsaLength(B(NLSR_LSA_HEADER_LENGTH).get());

        newAdjLSA->setM_adl(router->getAdjacencyList()); //add adjList to packet.
        router->installAdjLsa(newAdjLSA);
        delete newAdjLSA;
    }
    else{
        adjLsa->getHeaderForUpdate().setSeqNo(adjLsa->getHeader().getSeqNo() + 1);
        router->installAdjLsa(adjLsa);
    }
}

} // namespace nlsr
} // namespace inet




