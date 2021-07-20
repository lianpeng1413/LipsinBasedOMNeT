/*
 * NlsrRouter.h
 *
 *  Created on: Sep 4, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_NLSRROUTER_H_
#define INET_ROUTING_NLSR_ROUTER_NLSRROUTER_H_

#include <map>
#include <vector>
#include <iostream>

#include "../../../networklayer/ndnFlood/ndnFlood/ndnFlood.h"
#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/neighbor/adjacencyList.h"
#include "inet/routing/nlsr/router/namePrefixList.h"
#include "inet/routing/nlsr/router/route/namePrefixTable.h"
#include "inet/routing/nlsr/router/route/fib.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/router/route/routingTableEntry.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"

namespace inet{
namespace nlsr{
/**
 * All nlsr classes are in this namespace.
 */
class RoutingTable;
class MessageHandler;
class NlsrArea;
class NamePrefixTable;

class INET_API Router
{
private:
    IInterfaceTable *ifts = nullptr;
    RoutingTable *rt = nullptr;
    AdjacencyList* m_adjl  = nullptr;
    NamePrefixList* m_npl  = nullptr;
    Fib* m_fib  = nullptr;
    NamePrefixTable* m_namePrefixTable  = nullptr;  //create npt
    RouterName routerName;    ///< The router name assigned by the configure file.
    std::map<AreaId, NlsrArea *> areasByID; ///< A map of the contained areas with the AreaId as key.
    std::vector<NlsrArea *> areas;    ///< A list of the contained areas.

    std::map<iName, long> SequenceNumberMap;
    std::multimap<iName, NlsrInterface *> nameFromInterface;
    uint32_t m_maxFacesPerPrefix = 1;

    cMessage *ageTimer;    ///< Database age timer - fires every second.
    MessageHandler *messageHandler;   ///< The message dispatcher class.
    std::vector<Neighbor *> m_Neighbors; // maintain neighbor in each router
    int syncInterval;
    std::string RCTpath; //used for saving routing convergence results.
    double sendInterval;

  public:
    /** Constructor.
     * Initializes internal variables, adds a MessageHandler and starts the Database Age timer. */
    Router(cSimpleModule *containingModule, IInterfaceTable *ift, RoutingTable *rts, Fib *fib, int syncInterval, std::string RCTpath, double sendInterval);

    /** Destructor.
     * Clears all LSA lists and kills the Database Age timer.*/
    virtual ~Router();

    void setRouterID(RouterName id) { routerName = id; }
    RouterName getRouterID() const { return routerName; }
    unsigned long getAreaCount() const { return areas.size(); }
    std::vector<AreaId> getAreaIds();
    MessageHandler *getMessageHandler() { return messageHandler; }

    /* Adds OMNeT++ watches for the routerID, the list of Areas and the list of AS External LSAs. */
    void addWatches();

    /** Adds a new Area to the Area list.
     * @param area [in] The Area to add. */
    void addArea(NlsrArea *area);

    /**
     * Returns the pointer to the Area identified by the input areaID, if it's on the Area list,
     * nullptr otherwise.
     * @param areaID [in] The Area identifier.
     */
    NlsrArea *getAreaByID(AreaId areaID);

//    NlsrAdjLsa *getAdjLSA(unsigned long i) { return adjLsa.begin()+i; }
//    NlsrNameLsa *getNameLSA(unsigned long i) { return nameLsa.begin()+i; }

    int getNumInterface() { return ifts->getNumInterfaces();}
    InterfaceEntry *getInterface(int i) { return ifts->getInterface(i);}
    void addNeighbors(Neighbor *neighbor);
    long getNeighborNum() const { return m_Neighbors.size(); }
    Neighbor *getNeighbor(unsigned long i) { return m_Neighbors[i]; }
    uint32_t getMaxFacesPerPrefix(const iName& name);
    AdjacencyList* getAdjacencyList() { return m_adjl; }
    NamePrefixList* getNamePrefixList() { return m_npl; }
    NamePrefixTable* getNamePrefixTable() { return  m_namePrefixTable; }

    /*!Installs a interest name into LSDB. */
    void nameRegisterFunction(const iName& interest, iName & originRouter);

    /*! Installs name or adj LSA into the LSDB. */
    bool installNameLsa(const NlsrNameLsa* nlsa, AreaId areaID = BACKBONE_AREAID);
    bool installAdjLsa(const NlsrAdjLsa* alsa);

    /*!Returns the name LSA with the given Name.
      rName: The name of the router that the desired LSA comes from. */
    NlsrNameLsa* findNameLsa(const iName rName);

    /*! Finds an adj. LSA in the LSDB. */
    NlsrAdjLsa* findAdjLsa(const iName& keyName);

    /*! \brief Returns whether an LSA is new. This function determines
     * whether the LSA with the name and seqNo would be new to this LSDB. */
    bool isAdjLsaNew(const iName& keyName, uint64_t seqNo);

    std::vector<NlsrNameLsa *>& getNameLsdb();
    std::vector<NlsrAdjLsa *>& getAdjLsdb();

    /*! Returns whether a seq. no. from a certain router signals a new LSA.
      keyName: The name of the originating router.
      seqNo: The sequence number to check. */
    bool isNameLsaNew(const iName& keyName, uint64_t seqNo);

    /** Ages the LSAs in the Router's database.
     * This method is called on every firing of the DATABASE_AGE_TIMER(every second).*/
    void ageDatabase();

    /** Rebuilds the routing table from scratch(based on the LSA database). */
    void rebuildRoutingTable();
    short getSyncInterval() const { return syncInterval; }
    std::string getRCTpath() const { return RCTpath; }
    double getSendInterval() { return sendInterval;}
};

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_ROUTER_NLSRROUTER_H_ */
