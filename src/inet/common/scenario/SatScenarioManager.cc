/*
 * SatScenarioManager.cc
 *
 *  Created on: Mar 31, 2021
 *      Author: root
 */

#include "inet/common/scenario/SatScenarioManager.h"
#include "inet/common/scenario/ScenarioTimer_m.h"
#include <ctime>
#include <cstdlib>
namespace inet {

Define_Module(SatScenarioManager);
static const char *ATTR_T = "t";
static const char *ATTR_MODULE = "module";
static const char *ATTR_SRC_MODULE = "src-module";
static const char *ATTR_DEST_MODULE = "dest-module";
static const char *ATTR_SRC_GATE = "src-gate";
static const char *ATTR_DEST_GATE = "dest-gate";
static const char *ATTR_PAR = "par";
static const char *ATTR_NAME = "name";
static const char *ATTR_VALUE = "value";
static const char *ATTR_TYPE = "type";
static const char *ATTR_VECTOR = "vector";
static const char *ATTR_CHANNEL_TYPE = "channel-type";
static const char *ATTR_SUBMODULE = "submodule";
static const char *ATTR_PARENT = "parent";
static const char *ATTR_OPERATION = "operation";

static const char *CMD_AT = "at";
static const char *CMD_SET_PARAM = "set-param";
static const char *CMD_SET_CHANNEL_PARAM = "set-channel-param";
static const char *CMD_CREATE_MODULE = "create-module";
static const char *CMD_DELETE_MODULE = "delete-module";
static const char *CMD_CONNECT = "connect";
static const char *CMD_DISCONNECT = "disconnect";
static const char *CMD_INITIATE = "initiate";
static const char *TAG_PARAM = "param";

static const char *OP_START = "start";
static const char *OP_STARTUP = "startup";
static const char *OP_STOP = "stop";
static const char *OP_SHUTDOWN = "shutdown";
static const char *OP_CRASH = "crash";
static const char *OP_SUSPEND = "suspend";
static const char *OP_RESUME = "resume";

void SatScenarioManager::initialize()
{
    cXMLElement *script = par("script");
    intervals = par("intervals");
    numChanges = numDone = 0;
    WATCH(numChanges);
    WATCH(numDone);

    for (cXMLElement *node = script->getFirstChild(); node; node = node->getNextSibling()) {
        // check attr t is present
        const char *tAttr = node->getAttribute(ATTR_T);
        if (!tAttr)
            throw cRuntimeError("Attribute 't' missing at %s", node->getSourceLocation());

        // schedule self-message
        simtime_t t = SimTime::parse(tAttr);
        auto msg = new ScenarioTimer("scenario-event");
        msg->setXmlNode(node);
        scheduleAt(t, msg);

        // count it
        numChanges++;
    }
}

void SatScenarioManager::processAtCommand(const cXMLElement *node)
{
    const char *tAttr = node->getAttribute(ATTR_T);
    simtime_t t = SimTime::parse(tAttr);
    for (cXMLElement *child = node->getFirstChild(); child; child = child->getNextSibling()){
        std::string tag = child->getTagName();
        std::cout<<tag<<std::endl;
        if(tag == CMD_CONNECT){
            srand(time(0));
            double delayTime = ((double)rand())/(RAND_MAX) * intervals;
            t += SimTime(delayTime);
            auto msg = new ScenarioTimer("scenario-event");
            msg->setXmlNode(child);
            scheduleAt(t, msg);
        }else
            processCommand(child);
    }

}
} /* namespace inet */
