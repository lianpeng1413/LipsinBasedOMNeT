/*
 * LipsinLdTable.h
 *
 *  Created on: Mar 14, 2021
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_LIPSIN_LIPSINLDTABLE_H_
#define INET_NETWORKLAYER_LIPSIN_LIPSINLDTABLE_H_

#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/lipsin/LipsinLdEntry.h"
#include "inet/common/lifecycle/ILifecycle.h"

namespace inet {

class IInterfaceTable;

class INET_API LipsinLdTable : public cSimpleModule, public ILifecycle
{
private:
    IInterfaceTable *ift = nullptr;
    std::string tableName;
    bool forwarding = true;

    typedef std::vector<LipsinLdEntry *> LinkVector;
    LinkVector ldTable;
protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual bool handleOperationStage(LifecycleOperation *operation, IDoneCallback *doneCallback) override { return true;};

public:
    LipsinLdTable(){}
    ~LipsinLdTable(){ ldTable.clear();}
    virtual int getNumLds() const { return ldTable.size(); }
    virtual LipsinLdEntry *getLd(int k);
    void addEntry(LipsinLdEntry* entry);
    void updateEntryCost(const InterfaceEntry* entry,int cost);
    void updateEntryDistance(const InterfaceEntry* entry,int distance);
    std::vector<LipsinLdEntry *>  containsIntf(const InterfaceEntry* entry) const;
    void removeEntryByIntf(const InterfaceEntry* entry) ;
    void removeEntry(LipsinLdEntry* entry);
};



} /* namespace inet */

#endif /* INET_NETWORKLAYER_LIPSIN_LIPSINLDTABLE_H_ */
