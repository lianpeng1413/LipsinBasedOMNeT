/*
 * LipsinLdEntry.h
 *
 *  Created on: Mar 14, 2021
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_LIPSIN_LIPSINLDENTRY_H_
#define INET_NETWORKLAYER_LIPSIN_LIPSINLDENTRY_H_

#include "inet/common/INETDefs.h"
#include "inet/networklayer/common/InterfaceEntry.h"

namespace inet {

class InterfaceEntry;
class LipsinLdTable;

class INET_API LipsinLdEntry :public cObject
{
private:
    InterfaceEntry *interfacePtr;
    LipsinLdTable *ldt;
    int srcId; //src Host Id
    int destId;// dest Host Id
    int linkId; // src -- linkId --> dest
    int cost; //the cost between src and dest
    int distance = 4500; // the distance between src and dest

protected:
    //virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    //virtual void initialize(int stage) override{}
    //virtual void refreshDisplay() const override;
    //virtual void updateDisplayString() const;

public:
    LipsinLdEntry();
    LipsinLdEntry(InterfaceEntry* _interfacePtr,LipsinLdTable * _ldt,int _srcId,int _destId,int _linkId,int _cost);
    virtual ~LipsinLdEntry();
    std::string str() const override;
    bool operator==(const LipsinLdEntry& ldEntry) const { return equals(ldEntry); }
    bool operator!=(const LipsinLdEntry& ldEntry) const { return !equals(ldEntry); }
    bool equals(const LipsinLdEntry& ldEntry) const;
    virtual void setLipsinLdTable(LipsinLdTable *ldt) { this->ldt = ldt; }
    LipsinLdTable *getLipsinLdTable() const { return ldt; }
    virtual void setInterfaceEntry(InterfaceEntry *interfacePtr){ this->interfacePtr = interfacePtr; }
    InterfaceEntry *getInterfaceEntry() const { return interfacePtr; }
    virtual void setSrcId(int srcId){ this->srcId = srcId; }
    int getSrcId() const { return srcId; }
    virtual void setDestId(int destId){ this->destId = destId; }
    int getDestId() const { return destId; }
    virtual void setLinkId(int linkId){ this->linkId = linkId; }
    int getLinkId() const { return linkId; }
    virtual void setCost(int cost){ this->cost = cost; }
    int getDistance() const { return distance;}
    virtual void setDistance(int distance){ this->distance = distance; }
    int getCost() const { return cost; }
    virtual void changed(int changeCode) const;
};

} /* namespace inet */

#endif /* INET_NETWORKLAYER_LIPSIN_LIPSINLDENTRY_H_ */
