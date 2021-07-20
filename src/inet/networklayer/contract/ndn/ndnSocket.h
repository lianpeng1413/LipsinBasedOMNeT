/*
 * ndnSocket.h
 *
 *  Created on: Oct 2, 2020
 *      Author: root
 */

#ifndef INET_NETWORKLAYER_CONTRACT_NDN_NDNSOCKET_H_
#define INET_NETWORKLAYER_CONTRACT_NDN_NDNSOCKET_H_

#include "inet/networklayer/contract/ndn/iName.h"
#include "inet/common/INETDefs.h"
#include "inet/common/packet/Message.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/socket/ISocket.h"
#include "inet/common/Protocol.h"

namespace inet
{

class INET_API ndnSocket : public ISocket
{
public:

    class INET_API ICallback
    {
    public:
        virtual ~ICallback() {}

        /**
         * Notifies about data arrival, packet ownership is transferred to the callee.
         */
        virtual void socketDataArrived(ndnSocket *socket, Packet *packet) = 0;

        /**
         * Notifies about socket closed, indication ownership is transferred to the callee.
         */
        virtual void socketClosed(ndnSocket *socket) = 0;
    };
    enum State { CONNECTED, CLOSED};

protected:

      int socketId;
      ICallback *cb = nullptr;
      void *userData = nullptr;
      cGate *gateToInterest = nullptr;
      State sockState = CLOSED;

      ndnSocket::ICallback *callback = nullptr;
      cGate *outputGate = nullptr;
      bool bound = false;
      bool isOpen_ = false;
      const Protocol *l3Protocol = nullptr;

public:
      ndnSocket(const Protocol* protocol, cGate *outputGate = nullptr);
      ~ndnSocket(){};
      void *getUserData() const { return userData; }
      void setUserData(void *userData) { this->userData = userData; }
      void setOutputGate(cGate *outputGate) { this->outputGate = outputGate; }
      void bind(const Protocol *protocol, const iName &nid, int localPort);
      void setCallback(ndnSocket::ICallback *callback);
      int getSocketId() const override { return socketId; }
      void sendInterest(const iName &interest, int port, double inter);
      void cacheData(const iName &interest, cMessage *msg);
      void close();
      void destroy();
      const Protocol *getNetworkProtocol() const { return l3Protocol; };
      bool belongsToSocket(cMessage *msg) const;
      void processMessage(cMessage *msg) ;
      bool isOpen() const {return isOpen_;};
      void sendToOutput(cMessage *message);
      int generateSocketId(){ return getEnvir()->getUniqueNumber();}
};

}

#endif /* INET_NETWORKLAYER_CONTRACT_NDN_NDNSOCKET_H_ */
