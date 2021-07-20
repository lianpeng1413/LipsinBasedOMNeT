/*
 * Nlsr.h
 *
 *  Created on: Aug 23, 2020
 *      Author: root
 */

#ifndef INET_ROUTING_NLSR_NLSR_H_
#define INET_ROUTING_NLSR_NLSR_H_

#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

#include "inet/routing/base/RoutingProtocolBase.h"
#include "inet/routing/nlsr/NlsrPacket_m.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/neighbor/adjacencyList.h"
#include "inet/routing/nlsr/router/NlsrCommon.h"
#include "inet/routing/nlsr/router/namePrefixList.h"
#include "inet/routing/nlsr/router/route/namePrefixTable.h"
#include "router/route/fib.h"
#include "inet/routing/nlsr/router/route/routingTable.h"

namespace inet{
namespace nlsr {

//class RoutingTable;
//class Router;

class Nlsr : public RoutingProtocolBase, protected cListener
{
private:
    cModule *host = nullptr;    // the host module that owns this module
    RoutingTable *rt = nullptr;  // routingTable module
    IInterfaceTable *ift = nullptr;
    Fib* m_fib  = nullptr;
//    cacheTable *ct = nullptr;
    Router *nlsrRouter = nullptr;    // root object of the NLSR data structure
    cMessage *startupTimer = nullptr;    // timer for delayed startup
    int syncInterval;
    std::string RCTpath; //used for saving routing convergence results.
    double sendInterval; //used for test.

public:
    Nlsr();
    virtual ~Nlsr();

protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;
    virtual void subscribe();
    virtual void unsubscribe();
    virtual void createNlsrRouter();

    // lifecycle
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    void handleInterfaceDown(const InterfaceEntry *ie);
};

} // namespace nlsr
} // namespace inet

#endif /* INET_ROUTING_NLSR_NLSR_H_ */
