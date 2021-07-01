/*
 * LipsinLdEntry.cc
 *
 *  Created on: Mar 14, 2021
 *      Author: root
 */



#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/lipsin/LipsinLdEntry.h"


namespace inet {

Register_Class(LipsinLdEntry);

LipsinLdEntry::LipsinLdEntry()
{
    interfacePtr = nullptr;
    ldt = nullptr;
    srcId = 0;
    destId = 0;
    linkId = 0;
    cost = 0;
}
LipsinLdEntry::LipsinLdEntry(InterfaceEntry* _interfacePtr,LipsinLdTable * _ldt,int _srcId,int _destId,int _linkId,int _cost):
                interfacePtr(_interfacePtr),ldt(_ldt),srcId(_srcId),destId(_destId),linkId(_linkId),cost(_cost){}

std::string LipsinLdEntry::str() const
{
    std::stringstream out;
    out << srcId << " -- (linkID = " << linkId << " )--> " << destId << ", cost = " << cost ;
    out << " " << interfacePtr->str();
    return out.str();
}
bool LipsinLdEntry::equals(const LipsinLdEntry& ldEntry) const
{
    return (srcId == ldEntry.srcId) &&
            (linkId == ldEntry.linkId) &&
            (destId == ldEntry.destId) &&
            (cost == ldEntry.cost) &&
            (interfacePtr == ldEntry.interfacePtr);
}

LipsinLdEntry::~LipsinLdEntry() {
    // TODO Auto-generated destructor stub
}


void LipsinLdEntry::changed(int changeCode) const
{
    //TODO when need to dynamically adjust the Routing Table of LIPSIN
}

} /* namespace inet */
