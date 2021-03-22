/*
 * LipsinNetworkLayer.h
 *
 *  Created on: Mar 10, 2021
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_LIPSIN_LIPSINNETWORKLAYER_H_
#define INET_NETWORKLAYER_LIPSIN_LIPSINNETWORKLAYER_H_

#include "inet/common/INETDefs.h"

namespace inet {

class INET_API LipsinNetworkLayer: public cModule
{
protected:
    virtual void refreshDisplay() const override;
    virtual void updateDisplayString() const;
};

} /* namespace inet */

#endif /* INET_NETWORKLAYER_LIPSIN_LIPSINNETWORKLAYER_H_ */
