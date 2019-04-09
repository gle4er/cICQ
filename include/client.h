#ifndef CLIENT_H
#define CLIENT_H

#include "interface/interface.h"
#include "network/network.h"

class Client
{
private:
    Interface *interface;
    Network *network;
    int currentServerId = -1;

    int clientId = -1;

    void waitForAll();
    void enterCity();
    void waitForMove(int currPlayer);

public:
    Client(Interface *iface, Network *netw);
};

#endif
