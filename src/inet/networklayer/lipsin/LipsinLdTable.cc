/*
 * LipsinLdTable.cc
 *
 *  Created on: Mar 14, 2021
 *      Author: root
 */

#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/PatternMatcher.h"
#include "inet/common/Simsignals.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "LipsinLdTable.h"

namespace inet {
Define_Module(LipsinLdTable);

std::ostream& operator<<(std::ostream& os, const LipsinLdEntry& e)
{
    os << e.str();
    return os;
};

void LipsinLdTable::initialize(int stage)
{
    if(stage == INITSTAGE_LOCAL)
    {
        ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        forwarding = par("forwarding");
        const char * tabName = par("tableName");
        tableName = tabName;
        WATCH_PTRVECTOR(ldTable);
    }
}

LipsinLdEntry* LipsinLdTable::getLd(int k)
{
    if(k < (int) ldTable.size())
        return ldTable[k];
    return nullptr;
}

std::vector<LipsinLdEntry *> LipsinLdTable::containsIntf(const InterfaceEntry* entry) const
{
    std::vector<LipsinLdEntry *>  results;
    for(int i=0;i<ldTable.size();i++){
        if(ldTable[i]->getInterfaceEntry() == entry)
            results.push_back(ldTable[i]);
    }
    return results;
}

void LipsinLdTable::removeEntryByIntf(const InterfaceEntry* entry)
{
    for(int i=ldTable.size()-1;i>=0;i--)
        if(ldTable[i]->getInterfaceEntry() == entry){
            ldTable.erase(ldTable.begin()+i);
        }
}
void LipsinLdTable::removeEntry(LipsinLdEntry* entry)
{
    for(auto i=ldTable.begin();i!=ldTable.end();i++)
        if(*i == entry){
            ldTable.erase(i);
            EV_INFO << "Successfully delete the Entry ("<< entry->str()
                    << ") from " << tableName << endl;
            return;
        }
}
void LipsinLdTable::addEntry(LipsinLdEntry* entry)
{
    if(entry) ldTable.push_back(entry);
}
void LipsinLdTable::updateEntryCost(const InterfaceEntry* entry,int cost){
    for(int i=0;i<ldTable.size();i++){
        if(ldTable[i]->getInterfaceEntry() == entry){
            ldTable[i]->setCost(cost);
            std::cout << "Successfully update the Entry ("<< ldTable[i]->str()<<" ) from " << tableName << endl;
        }
    }
}

} /* namespace inet */
