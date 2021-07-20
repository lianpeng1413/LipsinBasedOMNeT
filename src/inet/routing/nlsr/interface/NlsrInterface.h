/*
 * NlsrInterface.h
 *
 *  Created on: Aug 25, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACE_H_
#define INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACE_H_

#include <list>
#include <map>
#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/router/NlsrArea.h"

namespace inet {

namespace nlsr {

class NlsrArea;
class NlsrInterfaceState;

class INET_API NlsrInterface
{
  public:
    // interface type define. We mainly use point-to-point type.
    enum NlsrInterfaceType {
        UNKNOWN_TYPE      = 0,
        POINTTOPOINT      = 1,
        POINTTOMULTIPOINT = 2
    };

    // There are many event type when interface state changed.
    enum NlsrInterfaceEventType {
        INTERFACE_UP      = 0,
        HELLO_TIMER       = 1,
        NEIGHBOR_CHANGE   = 2,
        INTERFACE_DOWN    = 3
    };

    enum NlsrInterfaceStateType {
        DOWN_STATE         = 0,
        POINTTOPOINT_STATE = 1,
        UNKNOWN_STATE      = 2
    };

    enum NlsrInterfaceMode {
        ACTIVE            = 0,
        PASSIVE           = 1,
        NO_NLSR           = 2
    };

  private:
    NlsrInterfaceType interfaceType;
    NlsrInterfaceMode interfaceMode;
    NlsrInterfaceState *state;
    NlsrInterfaceState *previousState;
    std::string interfaceName;
    int ifIndex;                   // fromIE
    MacAddress neighborMac;        // neighbor macAddress
    unsigned short mtu;
    AreaId areaID;
    AreaId transitAreaID;
    double helloInterval;
    double routerDeadInterval;
    cMessage *helloTimer;          // timer used to call retransmit hello interest
    std::map<iName, Neighbor *> neighboringRoutersByName; // maintain neighbor in interface
    std::vector<Neighbor *> neighboringRouters; // maintain neighbor in interface
    std::vector<iName> pendingRequestAdjLsaName; // pending sync interest name.
    std::vector<iName> pendingRequestNameLsaName;
    bool firstAdjacencyInited = false;
    bool firstNameInited = false;
    unsigned long nameLSASeqNumber = 0;
    unsigned long adjLSASeqNumber = 0;
    bool hasDiffer = true;
    static unsigned long nameLSASeqNumberInitSeed; // TODO: Should come from a global unique number generator module.
    static unsigned long adjLSASeqNumberInitSeed;
    Metric interfaceOutputCost;
    NlsrArea *parentArea;
    short syncInterval;

  private:
    friend class NlsrInterfaceState;
    void changeState(NlsrInterfaceState *newState, NlsrInterfaceState *currentState);

  public:
    NlsrInterface(NlsrInterfaceType ifType = POINTTOPOINT);
    virtual ~NlsrInterface();

    void processEvent(NlsrInterfaceEventType event);
    void reset();
    void initFirstAdjacency();
    void initFirstName();

    /*!Generate and sends a Hello Interest packet to the given adjacent.
     * Hello Interest: /Neighbor/HelloINFO/localRouter. */
    void sendHelloInterestPacket(iName destination, short ttl = 1);
    Neighbor *getNeighborByName(RouterName neighborName); // Get neighbors by names.
    void addNeighbor(Neighbor *neighbor);
    void removeNeighbor(iName neighbor);
    NlsrInterfaceStateType getState() const;
    static const char *getStateString(NlsrInterfaceStateType stateType);
    bool hasAnyNeighborInStates(int states) const;
    void addToPendingRequestAdjLsaNameList(iName& PRIN); //PendingRequestInterestName
    void addToPendingRequestNameLsaNameList(iName& PRIN);

    /*! Create and send a LSA Interest packet to the given adjacent.
     * Here that should be: /Neighbor/ADJINTERESTLSA/<localrouterName>. */
    void sendAdjLSAInterestPacket(iName requestName, iName destination, short ttl, Neighbor *neighbor);
    void sendNameLSAInterestPacket(iName requestName, iName destination, short ttl, Neighbor *neighbor);

    void setNameLSASeqNumber(unsigned long sequenceNumber) { nameLSASeqNumber = sequenceNumber; }
    unsigned long getNameLSASeqNumber() const { return nameLSASeqNumber; }
    void setAdjLSASeqNumber(unsigned long sequenceNumber) { adjLSASeqNumber = sequenceNumber; }
    unsigned long getAdjLSASeqNumber() const { return adjLSASeqNumber; }
    bool getWhetherFull();

    unsigned long getUniqueULong();
    unsigned long getNameULong();
    void incrementNameLSASeqNumber() { nameLSASeqNumber++; }
    void incrementAdjLSASeqNumber() { adjLSASeqNumber++; }
    void setType(NlsrInterfaceType ifType) { interfaceType = ifType; }
    NlsrInterfaceType getType() const { return interfaceType; }
    static const char *getTypeString(NlsrInterfaceType intfType);
    NlsrInterfaceMode getMode() const { return interfaceMode; }
    static const char *getModeString(NlsrInterfaceMode intfMode);
    void setMode(NlsrInterfaceMode intfMode) { interfaceMode = intfMode; }
    void setIfIndex(IInterfaceTable *ift, int index);
    void setIfToNeighbor(int index) { ifIndex = index; }
    int getIfIndex() const { return ifIndex; }
    void setInterfaceName(std::string ifName) { this->interfaceName = ifName; }
    std::string getInterfaceName() const { return interfaceName; }
    void setNeighborMac(MacAddress neighboringMac) { neighborMac = neighboringMac;};
    MacAddress getNeighborMac() const { return neighborMac; }
    void setMtu(unsigned short ifMTU) { mtu = ifMTU; }
    unsigned short getMtu() const { return mtu; }
    void setAreaId(AreaId areaId) { areaID = areaId; }
    AreaId getAreaId() const { return areaID; }
    void setTransitAreaId(AreaId areaId) { transitAreaID = areaId; }
    AreaId getTransitAreaId() const { return transitAreaID; }
    void setOutputCost(Metric cost) { interfaceOutputCost = cost; }
    Metric getOutputCost() const { return interfaceOutputCost; }
    void setHelloInterval(short interval) { helloInterval = interval; }
    short getHelloInterval() const { return helloInterval; }
    void setRouterDeadInterval(short interval) { routerDeadInterval = interval; }
    short getRouterDeadInterval() const { return routerDeadInterval; }
    cMessage *getHelloTimer() { return helloTimer; }
    unsigned long getNeighborCount() const { return neighboringRouters.size(); }
    Neighbor *getNeighbor(unsigned long i) { return neighboringRouters[i]; }
    const Neighbor *getNeighbor(unsigned long i) const { return neighboringRouters[i]; }

    void setArea(NlsrArea *area) { parentArea = area; }
    NlsrArea *getArea() { return parentArea; }
    const NlsrArea *getArea() const { return parentArea; }

    friend std::ostream& operator<<(std::ostream& stream, const NlsrInterface& intf);
};

} // namespace nlsr
} // namespace inet



#endif /* INET_ROUTING_NLSR_INTERFACE_NLSRINTERFACE_H_ */
