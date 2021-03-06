//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004-2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/applications/generic/IpvxTrafGen.h"
#include "inet/applications/generic/IpvxTrafSink.h"
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/networklayer/lipsin/LipsinHeader_m.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"

namespace inet {

Define_Module(IpvxTrafSink);

void IpvxTrafSink::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numReceived = 0;
        numTransitted = 0;
        WATCH(numReceived);
        WATCH(numTransitted);
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        int protocolId = par("protocol");
        if (protocolId < 143 || protocolId > 254)
            throw cRuntimeError("invalid protocol id %d, accepts only between 143 and 254", protocolId);
        auto protocol = ProtocolGroup::ipprotocol.findProtocol(protocolId);
        if (!protocol) {
            char *buff = new char[40];
            sprintf(buff, "prot_%d", protocolId);
            protocol = new Protocol(buff, buff);
            ProtocolGroup::ipprotocol.addProtocol(protocolId, protocol);
        }
        registerService(*protocol, nullptr, gate("ipIn"));
//        registerProtocol(*protocol, gate("ipOut"), nullptr);

        std::string nodeFullPath = this->getFullPath();
        std::smatch match;
        std::regex r("([[:w:]]+).LEO([0-9]+).([[:w:]]+)");
        bool found = regex_search(nodeFullPath,match,r);
        leoId = std::stoi(match.str(2));

        std::string fileName = "outSink.txt";
//        std::cout<<fileName<<std::endl<<leoId<<std::endl;
        outFile = new std::ofstream(fileName,std::ios::out|std::ios::app);
        if(!outFile->is_open()) throw cRuntimeError("Failed to open the file outSink.txt");
    }
}

void IpvxTrafSink::handleMessageWhenUp(cMessage *msg)
{
    processPacket(check_and_cast<Packet *>(msg));
}

void IpvxTrafSink::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[32];
    sprintf(buf, "rcvd: %d pks\n transit: %d pks", numReceived,numTransitted);
    getDisplayString().setTagArg("t", 0, buf);
}

void IpvxTrafSink::printPacket(Packet *msg)
{
    L3Address src, dest;
    int protocol = -1;
    auto ctrl = msg->getControlInfo();
    if (ctrl != nullptr) {
        protocol = ProtocolGroup::ipprotocol.getProtocolNumber(msg->getTag<PacketProtocolTag>()->getProtocol());
    }
    L3AddressTagBase *addresses = msg->findTag<L3AddressReq>();
    if (addresses == nullptr)
        addresses = msg->findTag<L3AddressInd>();
    if (addresses != nullptr) {
        src = addresses->getSrcAddress();
        dest = addresses->getDestAddress();
    }

    EV_INFO << msg << endl;
    EV_INFO << "Payload length: " << msg->getByteLength() << " bytes" << endl;

    if (ctrl != nullptr)
        EV_INFO << "src: " << src << "  dest: " << dest << "  protocol=" << protocol << endl;
}

void IpvxTrafSink::processPacket(Packet *msg)
{
    emit(packetReceivedSignal, msg);
    const auto & lipsinHeader = msg->removeAtFront<LipsinHeader>();
    const auto & ipHeader = msg->removeAtFront<Ipv4Header>();
    EV_INFO << leoId << " Received packet:";
    Ipv4Address addr(192,168,0,leoId);
    if(ipHeader->getDestAddress() == addr) {
        (*outFile)<<"Time:"<<simTime()<<"\t"<<ipHeader->getSrcAddress()<<"\t"<<ipHeader->getIdentification()<<std::endl;
        numReceived++;
    }

    printPacket(msg);

    msg->trim();
    delete msg;
    numTransitted++;

}
void IpvxTrafSink::handleStopOperation(LifecycleOperation *operation){
    (*outFile)<<leoId<<"\t"<<numReceived<<"\t"<<numTransitted<<std::endl;
    outFile->close();
    delete outFile;
}

} // namespace inet

