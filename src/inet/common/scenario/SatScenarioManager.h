/*
 * SatScenarioManager.h
 *
 *  Created on: Mar 31, 2021
 *      Author: root
 */

#ifndef INET_COMMON_SCENARIO_SATSCENARIOMANAGER_H_
#define INET_COMMON_SCENARIO_SATSCENARIOMANAGER_H_

#include "inet/common/scenario/ScenarioManager.h"
namespace inet {

class INET_API SatScenarioManager:public ScenarioManager {
private:
    int intervals = 0;
public:
    SatScenarioManager():ScenarioManager(){}
protected:
    virtual void processAtCommand(const cXMLElement *node) override;
    virtual void initialize() override;
};

} /* namespace inet */

#endif /* INET_COMMON_SCENARIO_SATSCENARIOMANAGER_H_ */
