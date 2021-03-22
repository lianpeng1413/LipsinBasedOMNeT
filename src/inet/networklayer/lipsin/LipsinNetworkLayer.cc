/*
 * LipsinNetworkLayer.cpp
 *
 *  Created on: Mar 10, 2021
 *      Author: root
 */

#include "inet/common/StringFormat.h"
#include "inet/networklayer/lipsin/LipsinNetworkLayer.h"

namespace inet {

Define_Module(LipsinNetworkLayer);

void LipsinNetworkLayer::refreshDisplay() const
{
    updateDisplayString();
}

void LipsinNetworkLayer::updateDisplayString() const
{
    auto text = StringFormat::formatString(par("displayStringTextFormat"), [&] (char directive) {
        static std::string result;
        switch (directive) {
            case 'i':
                //what does it mean???????
                result = getSubmodule("forwarder")->getDisplayString().getTagArg("t", 0);
                break;
            default:
                throw cRuntimeError("Unknown directive: %c", directive);
        }
        return result.c_str();
    });
    getDisplayString().setTagArg("t", 0, text);
}

} /* namespace inet */
