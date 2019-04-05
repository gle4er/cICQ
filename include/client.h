#ifndef CLIENT_H
#define CLIENT_H

#include "interface/interface.h"
#include "network/network.h"

#include <string>
#include <fstream>
#include <vector>

class Client {
private:
    struct Server {
        std::string ip;
        int port;
    };

    std::vector<Server> serverList;
    Interface *interface;
    Network *network;
    int currentServerId = -1;

    int clientId = -1;

    void loadServers(std::string);
    int connect();
    void waitForAll();
    void enterCity();
    void waitForMove();

public:
    Client(Interface *iface, Network *netw);
};

#endif
