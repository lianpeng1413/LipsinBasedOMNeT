/*
 * LipsinNeighborTable.h
 *
 *  Created on: Mar 14, 2021
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_LIPSIN_LIPSINNEIGHBORTABLE_H_
#define INET_NETWORKLAYER_LIPSIN_LIPSINNEIGHBORTABLE_H_

#include "inet/common/INETDefs.h"
namespace inet {

class INET_API LipsinNeighborTable : public cSimpleModule
{
public:
    LipsinNeighborTable();
    virtual ~LipsinNeighborTable();
};

} /* namespace inet */

#endif /* INET_NETWORKLAYER_LIPSIN_LIPSINNEIGHBORTABLE_H_ */
