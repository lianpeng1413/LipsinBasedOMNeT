/*
 * Nlsr.cc
 *
 *  Created on: Aug 23, 2020
 *      Author: root
 */
#include "Nlsr.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <map>
#include <memory.h>
#include <stdlib.h>

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/routing/nlsr/Nlsr.h"
#include "inet/routing/nlsr/NlsrConfigReader.h"
#include "inet/routing/nlsr/messageHandler/MessageHandler.h"
#include "inet/routing/nlsr/router/route/routingTable.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/neighbor/NlsrNeighbor.h"

namespace inet{
namespace nlsr {

Define_Module(Nlsr);

Nlsr::Nlsr()
{
}

Nlsr::~Nlsr()
{
    cancelAndDelete(startupTimer);
    delete nlsrRouter;
}

void Nlsr::initialize(int stage)
{
    RoutingProtocolBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        host = getContainingNode(this);

        auto name = getContainingNode(this)->getFullPath();
        name = name + ".interfaceTable";
        auto path = name.c_str();
        cModule *mod = this->getModuleByPath(path);
        ift = dynamic_cast<IInterfaceTable *>(mod);

        name = getParentModule()->getFullPath();
        name = name + ".routingTable";
        path = name.c_str();
        mod = this->getModuleByPath(path);
        rt = dynamic_cast<RoutingTable *>(mod);

        name = getParentModule()->getFullPath();
        name = name + ".fib";
        path = name.c_str();
        mod = this->getModuleByPath(path);
        m_fib = dynamic_cast<Fib *>(mod);

        startupTimer = new cMessage("NLSR-startup");
        syncInterval = par("syncInterval");
        RCTpath=par("RCTpath").stdstringValue();
        sendInterval = par("sendInterval");
    }
    else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {  // interfaces and static routes are already initialized
        registerService(Protocol::nlsr, nullptr, gate("ifIn"));
        registerProtocol(Protocol::nlsr, gate("ifOut"), nullptr);
    }
}

void Nlsr::handleMessageWhenUp(cMessage *msg)
{
    if (msg == startupTimer) { // receive startup msg -> create router.
        createNlsrRouter();
        subscribe();
    }
    else                      // other msg send to message handler.
        nlsrRouter->getMessageHandler()->messageReceived(msg);

}

void Nlsr::createNlsrRouter()
{
    nlsrRouter = new Router(this, ift, rt, m_fib, syncInterval,RCTpath,sendInterval);

    // read the configuration
    cXMLElement *nlsrConfig = par("nlsrConfig");
    NlsrConfigReader configReader(this, ift);
    if (!configReader.loadConfigFromXML(nlsrConfig, nlsrRouter))
        throw cRuntimeError("Error reading configuration from %s", nlsrConfig->getSourceLocation());

    nlsrRouter->addWatches();
}

void Nlsr::subscribe()
{
    host->subscribe(interfaceCreatedSignal, this);
    host->subscribe(interfaceDeletedSignal, this);
    host->subscribe(interfaceStateChangedSignal, this);
    host->subscribe(inet::cacheTable::nameRegisterTriggerSignal, this);
}

void Nlsr::unsubscribe()
{
    host->unsubscribe(interfaceCreatedSignal, this);
    host->unsubscribe(interfaceDeletedSignal, this);
    host->unsubscribe(interfaceStateChangedSignal, this);
    host->unsubscribe(inet::cacheTable::nameRegisterTriggerSignal, this);
}

/**
 * Listen on interface changes and update private data structures.
 */
void Nlsr::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
    Enter_Method("nlsr::receiveSignal");

    const InterfaceEntry *ie;
    const InterfaceEntryChangeDetails *change;

    if (signalID == interfaceCreatedSignal) {
        // configure interface for other routing protocol
        ie = check_and_cast<const InterfaceEntry *>(obj);
        if (ie->isMulticast() && !ie->isLoopback()) {
            // TODO
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
            if (!ie->isUp())
                handleInterfaceDown(ie);
            else {
                // initialize interface, send hello interest to establish adjacency.
                NlsrInterface *foundIntf = nullptr;
                for(auto &areaId : nlsrRouter->getAreaIds()) {
                    NlsrArea *area = nlsrRouter->getAreaByID(areaId);
                    if(area){
                        for(auto &ifIndex : area->getInterfaceIndices()){
                            NlsrInterface *intf = area->getInterface(ifIndex);
                            if(intf && intf->getIfIndex() == ie->getInterfaceId()) {
                                foundIntf = intf;
                                break;
                            }
                        }
                        if(foundIntf) {
                            foundIntf->processEvent(NlsrInterface::INTERFACE_UP);
                            break;
                        }
                    }
                }
            }
        }
    }
    else if (signalID == inet::cacheTable::nameRegisterTriggerSignal) {
        EV_INFO << "Received name register notification." << std::endl;
        auto nameRegisterSignal = check_and_cast<inet::cacheTable::nameRegister *>(obj);
        nlsrRouter->nameRegisterFunction(nameRegisterSignal->name, nameRegisterSignal->originalRouter);
    }
    else
        throw cRuntimeError("Unexpected signal: %s", getSignalName(signalID));
}

void Nlsr::handleStartOperation(LifecycleOperation *operation)
{
    ASSERT(nlsrRouter == nullptr);
    simtime_t startupTime = par("startupTime");
    if (startupTime <= simTime()) {
        createNlsrRouter();
        subscribe();
    }
    else
        scheduleAt(simTime() + startupTime, startupTimer);
}

void Nlsr::handleStopOperation(LifecycleOperation *operation)
{
    ASSERT(nlsrRouter);
    delete nlsrRouter;
    cancelEvent(startupTimer);
    nlsrRouter = nullptr;
    unsubscribe();
}

void Nlsr::handleCrashOperation(LifecycleOperation *operation)
{
    ASSERT(nlsrRouter);
    delete nlsrRouter;
    cancelEvent(startupTimer);
    nlsrRouter = nullptr;
    unsubscribe();
}

void Nlsr::handleInterfaceDown(const InterfaceEntry *ie) //TODO modify delete direct routes.
{
    EV_DEBUG << "interface " << ie->getInterfaceId() << " went down. \n";

    // Step 1: delete all fib items connected to this interface
    m_fib->updateNextHop(ie->getInterfaceId());

    // Step 2: find the NlsrInterface associated with the ie and take it down
    NlsrInterface *foundIntf = nullptr;
    for(auto &areaId : nlsrRouter->getAreaIds()) {
        NlsrArea *area = nlsrRouter->getAreaByID(areaId);
        if(area){
            for(auto &ifIndex : area->getInterfaceIndices()){
                NlsrInterface *intf = area->getInterface(ifIndex);
                if(intf && intf->getIfIndex() == ie->getInterfaceId()) {
                    foundIntf = intf;
                    break;
                }
            }
            if(foundIntf && foundIntf->getState() != NlsrInterface::DOWN_STATE) {
                foundIntf->processEvent(NlsrInterface::INTERFACE_DOWN);
                break;
            }
        }
    }
}

} // namespace nlsr
} // namespace inet

