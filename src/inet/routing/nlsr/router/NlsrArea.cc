/*
 * NlsrArea.cc
 *
 *  Created on: Dec 1, 2020
 *      Author: root
 */

#include <memory.h>

#include "inet/routing/nlsr/router/NlsrArea.h"
#include "inet/routing/nlsr/router/NlsrRouter.h"
#include "inet/routing/nlsr/router/route/namePrefixTable.h"

namespace inet {

namespace nlsr {

NlsrArea::NlsrArea(IInterfaceTable *ift, AreaId id) :
    ift(ift),
    areaID(id),
    stubDefaultCost(1),
    parentRouter(nullptr)
{
}

NlsrArea::~NlsrArea()
{
    for (auto interface : associatedInterfaces)
        delete (interface);
    associatedInterfaces.clear();

    for (auto nameLSA : nameLsa)
        delete nameLSA;
    nameLsa.clear();

    for (auto adjLSA : adjLsa)
        delete adjLSA;
    adjLsa.clear();
}

void NlsrArea::addWatches()
{
//    WATCH_PTRVECTOR(nameLsa);
//    WATCH_PTRVECTOR(adjLsa);
//    WATCH_PTRVECTOR(associatedInterfaces);
}

void NlsrArea::addInterface(NlsrInterface *intf)
{
    intf->setArea(this);
    associatedInterfaces.push_back(intf);
}

void NlsrArea::deleteInterface(NlsrInterface *intf)
{
    EV_INFO << "delete interface: " << intf->getIfIndex()<< endl;
    for(auto it = associatedInterfaces.begin();it != associatedInterfaces.end();it++){
        if((*it)->getIfIndex() == intf->getIfIndex()){
            delete (*it);
            it = associatedInterfaces.erase(it);
        }
    }
}

std::string NlsrArea::str() const
{
    return std::to_string(areaID);
}

std::string NlsrArea::info() const
{
    std::stringstream out;

    out << "areaID: " << std::to_string(areaID) << ", ";
    out << "stubDefaultCost: " << stubDefaultCost << ", ";
    for (uint32_t i = 0; i < associatedInterfaces.size(); i++) {
        out << "interface[" << i << "]: ";
    }

    return out.str();
}

std::string NlsrArea::detailedInfo() const
{
    std::stringstream out;

    out << info();

    out << "nameLSAs:\n";
    for (auto &entry : nameLsa)
        out << "        " << entry << "\n";
    out << "adjLSAs:\n";
    for (auto &entry : adjLsa)
        out << "        " << entry << "\n";

    return out.str();
}

NlsrInterface *NlsrArea::getInterface(unsigned char ifIndex)
{
    int interfaceNum = associatedInterfaces.size();
    for (int i = 0; i < interfaceNum; i++) {
        if (associatedInterfaces[i]->getIfIndex() == ifIndex)
        {
            return associatedInterfaces[i];
        }
    }
    return nullptr;
}

std::vector<int> NlsrArea::getInterfaceIndices()
{
    std::vector<int> indices;
    for(auto &intf : associatedInterfaces)
        indices.push_back(intf->getIfIndex());
    return indices;
}

NlsrNameLsa* NlsrArea::findNameLsa(const iName rName)
{// find "rName" in lsdb whether or not.
    for (auto it = nameLsa.begin(); it != nameLsa.end(); it++) {
        if ((*it)->getHeader().getInterestName() == rName){
            NlsrNameLsa* nameLsa;
            nameLsa = *it;
            return nameLsa;
        }
    }
    return nullptr;
}

bool NlsrArea::isAdjLsaNew(const iName& key, uint64_t seqNo)
{
    NlsrAdjLsa* adjLsaCheck = findAdjLsa(key);
    // If it is in the LSDB
    if (adjLsaCheck != nullptr) {
    // And the supplied seq no is newer (higher) than the current one.
        if (adjLsaCheck->getHeader().getSeqNo() < seqNo) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}

bool NlsrArea::installNameLsaToLsdb(const NlsrNameLsa* nlsa)
{
    EV_INFO << "Install NameLsa:" << nlsa->getHeader().getInterestName().str() << " to LSDB."<< endl;

    iName LsaName = nlsa->getHeader().getInterestName();
    NlsrNameLsa* chkNameLsa = findNameLsa(LsaName);

    // Determines if the name LSA is new or not.
    if (chkNameLsa == nullptr) {
        if(nlsa->getHeader().getOriginRouter() != parentRouter->getRouterID()) {
            //if this name LSA from another router, add the advertised prefix to the NPT
            parentRouter->getNamePrefixTable()->addEntry(nlsa->getHeader().getOriginRouter(), nlsa->getHeader().getOriginRouter());
            for(const auto&name : nlsa->getM_npl()->getNames()){
                parentRouter->getNamePrefixTable()->addEntry(name, nlsa->getHeader().getOriginRouter());
            }
        }
        nameLsa.push_back(nlsa->dup());// insert into nameLsa list.

//        recoderUpdateTimes("LSDBchangedTime.txt"); // record the time when lsdb changed.
    }
    // Else this is a known name LSA, so we are updating it.
    else {
        EV_INFO << "Known name lsa."
                << "chkNameLsa->getSeqNo(): " << chkNameLsa->getHeader().getSeqNo() << "\n.";
        EV_INFO << "nlsa.getSeqNo(): " << nlsa->getHeader().getSeqNo() << "\n";
        if (chkNameLsa->getHeader().getSeqNo() < nlsa->getHeader().getSeqNo()) {
            EV_INFO <<  "Updated Name LSA. Updating LSDB." << "Name Lsa: "
                    << chkNameLsa->getHeader().getInterestName().str();
            chkNameLsa->getHeaderForUpdate().setSeqNo(nlsa->getHeader().getSeqNo());
            chkNameLsa->getM_nplForUpdate()->sort();

            NlsrNameLsa *lsaCopy = new NlsrNameLsa(*nlsa);
            lsaCopy->getM_nplForUpdate()->sort();
            // Obtain the difference of the ownNPL and rcvNPL
            // name prefix sets, and add those.
            std::list<iName> newNames = lsaCopy->getM_npl()->getNames();
            std::list<iName> oldNames = chkNameLsa->getM_npl()->getNames();
            std::list<iName> namesToAdd;
            std::set_difference(newNames.begin(), newNames.end(), oldNames.begin(), oldNames.end(),
                                std::inserter(namesToAdd, namesToAdd.begin()));
            for(const auto& name : namesToAdd) {
                chkNameLsa->getM_nplForUpdate()->insert(name);
            }
            if(lsaCopy->getHeader().getOriginRouter() != parentRouter->getRouterID()) {
                //if this name LSA from another router, add the advertised prefix to the NPT
                parentRouter->getNamePrefixTable()->addEntry(lsaCopy->getHeader().getOriginRouter(), lsaCopy->getHeader().getOriginRouter());
            }
            chkNameLsa->getM_nplForUpdate()->sort();

            // Also remove any names that are no longer being advertised.
            std::list<iName> namesToRemove;
            std::set_difference(oldNames.begin(), oldNames.end(), newNames.begin(), newNames.end(),
                                std::inserter(namesToRemove, namesToRemove.begin()));
            for (const auto& name : namesToRemove) {
              EV_INFO << "Removing name LSA no longer advertised: " << name.str() << endl;
              chkNameLsa->getM_nplForUpdate()->remove(name);
              parentRouter->getNamePrefixTable()->removeEntry(name, lsaCopy->getHeader().getOriginRouter());
            }
            delete lsaCopy;
        }
//        recoderUpdateTimes("LSDBchangedTime.txt"); // record the time when lsdb changed.
    }
    return true;
}

bool NlsrArea::doesNameLsaExist(const iName& key)
{
    for (auto iter = nameLsa.begin();iter != nameLsa.end();iter++) {
        if ((*iter)->getHeader().getInterestName() == key){
            return true;
        }
    }
    return false;
}

bool NlsrArea::removeNameLsa(const iName& key)
{
    for (auto it = nameLsa.begin();it != nameLsa.end(); it++) {
        if ((*it)->getHeader().getInterestName() == key){
            EV_INFO << "Deleting Name Lsa" << key.str() << endl;
            // If the requested name LSA is not ours, we also need to remove its entries from the NPT.
            parentRouter->getNamePrefixTable()->removeEntry((*it)->getHeader().getInterestName(), (*it)->getHeader().getOriginRouter());
            nameLsa.erase(it);

            //Sync will be triggered after nameLsa removed.
            int neighborCount = parentRouter->getAdjacencyList()->getAdjList().size();
            for(int i = 0; i < neighborCount; i++ ){
                parentRouter->getNeighbor(i)->sendSyncInterestPacket();
            }
            return true;
        }
    }
    return false;
}

bool NlsrArea::isNameLsaNew(const iName& key, uint64_t seqNo)
{
    NlsrNameLsa* nameLsaCheck = findNameLsa(key);
    // Is the name in the LSDB
    if (nameLsaCheck != nullptr) {
        // And the supplied seq no is the highest so far
        if (nameLsaCheck->getHeader().getSeqNo() < seqNo) {
            return true;
        }
        else {
            return false;
        }
    }
    else{
        return true;
    }
}

std::vector<NlsrNameLsa *>& NlsrArea::getNameLsdb()
{
//    std::ofstream adjLsaInfo;
//    auto adjLsaFile = std::string("nameLSDB.txt");
//    adjLsaInfo.open(adjLsaFile, std::ofstream::app);
//    adjLsaInfo << parentRouter->getRouterID().str() << ", at time = " << simTime() << endl;
//
//    auto it = nameLsa.begin();
//    for ( ; it!= nameLsa.end(); it++){
//        adjLsaInfo << (*it)->getHeader().getInterestName()<< endl;
//        auto adjL = (*it)->getM_npl()->getNames();
//        auto adjPTR = adjL.begin();
//        for ( ; adjPTR!= adjL.end(); adjPTR++){
//            adjLsaInfo << "names in npl: " << (*adjPTR).str() << endl;
//        }
//    }
//    adjLsaInfo.close();

    return nameLsa;
}

bool NlsrArea::removeAdjLsa(const iName& key)
{
    for (auto it = adjLsa.begin();it != adjLsa.end(); it++) {
        if ((*it)->getHeader().getInterestName() == key){
            EV_INFO << "Deleting Adj Lsa" << key.str() << endl;
            // If the requested name LSA is not ours, we also need to remove its entries from the NPT.
            parentRouter->getNamePrefixTable()->removeEntry((*it)->getHeader().getInterestName(), (*it)->getHeader().getOriginRouter());
            adjLsa.erase(it); //delete item.
            return true;
        }
    }
    return false;
}

NlsrAdjLsa* NlsrArea::findAdjLsa(const iName& key)
{// find "key" in lsa whether or not.
    for (auto it = adjLsa.begin(); it != adjLsa.end(); it++) {
        if ((*it)->getHeader().getInterestName() == key){
            NlsrAdjLsa* adjLSA;
            adjLSA = *it;
            return adjLSA;
        }
    }
    return nullptr;
}

bool NlsrArea::installAdjLsaToLsdb(const NlsrAdjLsa* alsa)
{
    iName LsaName = alsa->getHeader().getInterestName();
    NlsrAdjLsa* chkAdjLsa = findAdjLsa(LsaName);

    // If this adj. LSA is not in the LSDB already
    if (chkAdjLsa == nullptr) {
        EV_INFO << "New Adj LSA. Adding to LSDB. \n" << "Adding Adj Lsa: " << alsa->getHeader().getInterestName().str() << endl;
        adjLsa.push_back(alsa->dup());// insert into adj lsa vector.

        //New lsa added, trigger pendingEntries retrieve.
        parentRouter->getMessageHandler()->getSyncHandler()->satisfyPendingInterests();
        parentRouter->rebuildRoutingTable();  // add adj lsa and update rebuild routingTable TODO

//        if(simTime().dbl() > 288.0)
//        recoderUpdateTimes("LSDBchangedTime.txt"); // record the time when lsdb changed.
    }
    // Else this is a known adj LSA with a larger seqNo, so we are updating it.
    else {
        if (chkAdjLsa->getHeader().getSeqNo() < alsa->getHeader().getSeqNo()) {
            EV_INFO << "Updated Adj LSA. Updating LSDB." << chkAdjLsa->getHeader().getInterestName().str() << endl;
            removeAdjLsa(LsaName);
            adjLsa.push_back(alsa->dup());// insert into adj lsa vector.

            //New lsa added, trigger pendingEntries retrieve.
            parentRouter->getMessageHandler()->getSyncHandler()->satisfyPendingInterests();
            parentRouter->rebuildRoutingTable();// add adj lsa and update rebuild routingTable TODO

//            if(simTime().dbl() > 288.0)
//            recoderUpdateTimes("LSDBchangedTime.txt"); // record the time when lsdb changed.
        }
    }
    return true;
}

bool NlsrArea::doesAdjLsaExist(const iName& key)
{
    for (auto iter = adjLsa.begin();iter != adjLsa.end();iter++) {
        if ((*iter)->getHeader().getInterestName() == key){
            return true;
        }
    }
    return false;
}

std::vector<NlsrAdjLsa *>& NlsrArea::getAdjLsdb()
{
//    std::ofstream adjLsaInfo;
//    auto adjLsaFile = std::string("adjLSDB.txt");
//    adjLsaInfo.open(adjLsaFile, std::ofstream::app);
//    adjLsaInfo << parentRouter->getRouterID().str() << ", at time = " << simTime() << endl;
//    auto it = adjLsa.begin();
//    for ( ; it!= adjLsa.end(); it++){
//        adjLsaInfo << (*it)->getHeader().getInterestName()<< ",seqNo: " << (*it)->getHeader().getSeqNo() << endl;
//        auto adjL = (*it)->getM_adl()->getAdjList();
//        auto adjPTR = adjL.begin();
//        for ( ; adjPTR!= adjL.end(); adjPTR++){
//            adjLsaInfo << "names in adjl: " << (*adjPTR)->getNeighborName().str() << ", cost = " << (*adjPTR)->getLinkCost() << endl;
//        }
//    }
//    adjLsaInfo.close();

    return adjLsa;
}

void NlsrArea::ageDatabase()
{
    bool shouldRebuildRoutingTable = false;

    for (auto lsa: nameLsa) {
        unsigned short lsAge = lsa->getHeader().getLsAge();
        bool selfOriginated = (lsa->getHeader().getOriginRouter() == parentRouter->getRouterID() );

        if ((selfOriginated && (lsAge < (MAX_AGE - 1))) || (!selfOriginated && (lsAge < (MAX_AGE - 1))))
        {
            lsa->getHeaderForUpdate().setLsAge(lsAge + 1);
        }

        if (selfOriginated && (lsAge == (MAX_AGE - 1))) {
            long sequenceNumber = lsa->getHeader().getSeqNo();
            if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
                lsa->getHeaderForUpdate().setLsAge(MAX_AGE);
                removeNameLsa(lsa->getHeader().getInterestName());
                shouldRebuildRoutingTable = true;
            }
            else {
                lsa->getHeaderForUpdate().setSeqNo(sequenceNumber + 1);
            }
        }

        if (!selfOriginated && (lsAge == MAX_AGE - 1)) {
            lsa->getHeaderForUpdate().setLsAge(MAX_AGE);
            removeNameLsa(lsa->getHeader().getInterestName());
            shouldRebuildRoutingTable = true;
        }
    }

    auto nameIt = nameLsa.begin();
    while (nameIt != nameLsa.end()) {
        if ((*nameIt) == nullptr) {
            nameIt = nameLsa.erase(nameIt);
        }
        else {
            nameIt++;
        }
    }

    for (auto lsa: adjLsa) {
        unsigned short lsAge = lsa->getHeader().getLsAge();
        bool selfOriginated = (lsa->getHeader().getOriginRouter() == parentRouter->getRouterID() );

        if ((selfOriginated && (lsAge < (MAX_AGE - 1))) || (!selfOriginated && (lsAge < (MAX_AGE - 1))))
        {
            lsa->getHeaderForUpdate().setLsAge(lsAge + 1);
        }

        if (selfOriginated && (lsAge == (MAX_AGE - 1))) {
            long sequenceNumber = lsa->getHeader().getSeqNo();
            if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
                lsa->getHeaderForUpdate().setLsAge(MAX_AGE);
                removeAdjLsa(lsa->getHeader().getInterestName());
                shouldRebuildRoutingTable = true;
            }
            else {
                lsa->getHeaderForUpdate().setSeqNo(sequenceNumber + 1);
            }
        }

        if (!selfOriginated && (lsAge == MAX_AGE - 1)) {
            lsa->getHeaderForUpdate().setLsAge(MAX_AGE);
            removeAdjLsa(lsa->getHeader().getInterestName());
            shouldRebuildRoutingTable = true;
        }
    }

    auto adjIt = adjLsa.begin();
    while (adjIt != adjLsa.end()) {
        if ((*adjIt) == nullptr) {
            adjIt = adjLsa.erase(adjIt);
        }
        else {
            adjIt++;
        }
    }

    if (shouldRebuildRoutingTable){
        parentRouter->rebuildRoutingTable();
    }
}

bool NlsrArea::hasAnyNeighborInStates(int states) const
{
    for (uint32_t i = 0; i < associatedInterfaces.size(); i++) {
        if (associatedInterfaces[i]->hasAnyNeighborInStates(states))
            return true;
    }
    return false;
}

//Recorder function
void NlsrArea::recoderUpdateTimes(std::string fileName)
{
    path = this->parentRouter->getRCTpath();
    fileName = std::string("LsdbUpdateTime_") + std::to_string(this->parentRouter->getSyncInterval()) + std::string("_") +
            std::to_string(this->parentRouter->getSendInterval());

    std::ofstream outfile;
    outfile.open(path + fileName + std::string(".txt"), std::ofstream::app);
    simtime_t time = simTime();
    outfile << "lsdb changed at: " << time << endl;
    outfile.close();
}

void NlsrArea::printLSDB()
{
    // iterate over all nameLSA in all routers inside this area
    for (uint32_t i = 0; i < nameLsa.size(); i++) {
        NlsrNameLsa *entry = check_and_cast<NlsrNameLsa *>(nameLsa[i]);

        const NlsrLsaHeader &head = entry->getHeader();
        std::string routerId = head.getInterestName().str();
        EV_INFO << "name LSA in Area " << std::to_string(areaID) << " in nlsr router with ID " << routerId << std::endl;

        // print header info
        EV_INFO << "    LS age: " << head.getLsAge() << std::endl;
        EV_INFO << "    LS type: " << head.getLsType() << std::endl;
        EV_INFO << "    Seq number: " << head.getSeqNo() << std::endl;
        EV_INFO << "    Length: " << head.getLsaLength() << std::endl;

        EV_INFO << "    Number of interest names: " << entry->getM_npl()->size() << std::endl << std::endl;
        for(unsigned int j = 0; j < entry->getM_npl()->size(); j++) {
            const auto &nameList = entry->getM_npl()->getNames();

            EV_INFO << "   name list: " << std::endl;
//            for(int k=0; k < nameList.size(); k++)
//                EV_INFO << "      " << nameList[k] << std::endl;
        }
    }

    // iterate over all adjLSA in all routers inside this area
    for (unsigned int i = 0; i < adjLsa.size(); i++) {
        EV_INFO << "adj LSA in Area " << std::to_string(areaID) << std::endl;
        NlsrAdjLsa *entry = check_and_cast<NlsrAdjLsa *>(adjLsa[i]);

        // print header info
        const NlsrLsaHeader &head = entry->getHeader();
        EV_INFO << "    LS age: " << head.getLsAge() << std::endl;
        EV_INFO << "    LS type: " << head.getLsType() << std::endl;
        EV_INFO << "    Seq number: " << head.getSeqNo() << std::endl;
        EV_INFO << "    Length: " << head.getLsaLength() << std::endl;

        EV_INFO << "    Number of neighbors: " << entry->getM_adl()->getAdjList().size()<< std::endl;
        for(unsigned int j = 0; j < entry->getM_adl()->getAdjList().size(); j++) {
            const auto &neighborList = entry->getM_adl()->getAdjList();

            EV_INFO << "   neighbor list: " << std::endl;
//            for(int k=0; k < neighborList.size(); k++)
//                EV_INFO << "      " << neighborList[k] << std::endl;
        }
    }
}

} // namespace nlsr
} // namespace inet



