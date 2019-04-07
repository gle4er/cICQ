#ifndef TCP_H
#define TCP_H

#include "network/network.h"
#include <vector>
#include <string>

class TCPNetwork : public Network {
protected:
    struct Server {
        std::string ip;
        int port;
    };
    std::vector<Server> serverList;
	int sock_fd;

public:
    int setSocket(std::string, int);

    bool checkCity(std::string);
    int establishServer();
    int getClientId();
    int getCurrPlayer();
    void getMessages(char *);
    TCPNetwork();
    TCPNetwork(std::string);
    ~TCPNetwork();
};

#endif
