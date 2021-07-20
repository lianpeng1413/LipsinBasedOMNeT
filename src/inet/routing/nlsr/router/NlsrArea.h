/*
 * NlsrArea.h
 *
 *  Created on: Dec 1, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_ROUTER_NLSRAREA_H_
#define INET_ROUTING_NLSR_ROUTER_NLSRAREA_H_

#include <map>
#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/nlsr/interface/NlsrInterface.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
//#include "inet/routing/nlsr/router/NlsrRoutingTableEntry.h"

namespace inet {
namespace nlsr {

class Router;
//class NamePrefixTable;

class INET_API NlsrArea : public cObject
{
private:
    IInterfaceTable *ift;
    AreaId areaID;
    std::vector<iName> nameRegisterTable;  // used to record registered names.
    std::vector<NlsrInterface *> associatedInterfaces;
    std::vector<HostRouteParameters> hostRoutes;
    std::vector<NlsrNameLsa* > nameLsa;    ///< A list of the contained nameLsa.
    std::vector<NlsrAdjLsa* > adjLsa;    ///< A list of the contained adjLsa.
    Metric stubDefaultCost;

    Router *parentRouter;
    std::string path; //used for saving routing convergence results.

public:
  NlsrArea(IInterfaceTable *ift, AreaId id = BACKBONE_AREAID);
  virtual ~NlsrArea();

  void setAreaID(AreaId areaId) { areaID = areaId; }
  AreaId getAreaID() const { return areaID; }
  void addHostRoute(HostRouteParameters& hostRouteParameters) { hostRoutes.push_back(hostRouteParameters); }
  void setStubDefaultCost(Metric cost) { stubDefaultCost = cost; }
  Metric getStubDefaultCost() const { return stubDefaultCost; }
  void setRouter(Router *router) { parentRouter = router; }
  Router *getRouter() { return parentRouter; }
  const Router *getRouter() const { return parentRouter; }
  unsigned long getNameLSACount() const { return nameLsa.size(); }
  NlsrNameLsa *getNameLSA(unsigned long i) { return nameLsa[i]; }
  const NlsrNameLsa *getNameLSA(unsigned long i) const { return nameLsa[i]; }
  unsigned long getAdjLSACount() const { return adjLsa.size(); }
  NlsrAdjLsa *getAdjLSA(unsigned long i) { return adjLsa[i]; }
  const NlsrAdjLsa *getAdjLSA(unsigned long i) const { return adjLsa[i]; }

  void addWatches();
  void addInterface(NlsrInterface *intf);
  void deleteInterface(NlsrInterface *intf);
  int getInterfaceCount() const {return associatedInterfaces.size();}
  NlsrInterface *getInterface(unsigned char ifIndex);
  std::vector<int> getInterfaceIndices();

  //Functions related to Name LSDB
  /*!Returns the name LSA with the given Name.
    rName: The name of the router that the desired LSA comes from. */
  NlsrNameLsa* findNameLsa(const iName rName);

  /*!Installs a name LSA into the LSDB. */
  bool installNameLsaToLsdb(const NlsrNameLsa* nlsa);

  /*! \brief Remove a name LSA from the LSDB, and trigger update name prefix
    key: The name of the router that published the LSA to remove. */
  bool removeNameLsa(const iName& key);

  /*! Returns whether a seq. no. from a certain router signals a new LSA.
    keyName: The name of the originating router.
    seqNo: The sequence number to check. */
  bool isNameLsaNew(const iName& keyName, uint64_t seqNo);

  std::vector<NlsrNameLsa *>& getNameLsdb();

  /*! Returns whether the LSDB contains some LSA.  */
  bool doesNameLsaExist(const iName& keyName);

  //Functions related to Adj LSDB
  /*!Removes an adj. LSA from the LSDB.
    keyName: The name of the publishing router whose LSA to remove. */
  bool removeAdjLsa(const iName& key);

  /*! \brief Returns whether an LSA is new. This function determines
   * whether the LSA with the name and seqNo would be new to this LSDB. */
  bool isAdjLsaNew(const iName& keyName, uint64_t seqNo);

  /*! Installs an adj. LSA into the LSDB. */
  bool installAdjLsaToLsdb(const NlsrAdjLsa* alsa);

  /*! Finds an adj. LSA in the LSDB. */
  NlsrAdjLsa* findAdjLsa(const iName& keyName);

  std::vector<NlsrAdjLsa *>& getAdjLsdb();

  /*! Returns whether the LSDB contains an LSA. */
  bool doesAdjLsaExist(const iName& keyName);

  void ageDatabase();
  bool hasAnyNeighborInStates(int states) const;

  //Recording routing convergence and update times.20210107 by YF
  void recoderUpdateTimes(std::string fileName);//, const  NlsrAdjLsa * alsa, const  NlsrNameLsa * nlsa);

  void printLSDB();
  std::string str() const override;
  std::string info() const OMNETPP5_CODE(override);
  std::string detailedInfo() const OMNETPP5_CODE(override);
};

inline std::ostream& operator<<(std::ostream& ostr, NlsrArea& area)
{
  ostr << area.info();
  return ostr;
}

} // nlsr namespace
} // inet namespace

#endif /* INET_ROUTING_NLSR_ROUTER_NLSRAREA_H_ */
