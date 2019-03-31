#ifndef CLIENT_H
#define CLIENT_H

#include "interface/interface.h"
#include "network/network.h"

#include <string>
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

    std::string getInput();
    void loadServers(std::string);
    void connect();

public:
    Client(Interface *iface, Network *netw);
};

#endif
