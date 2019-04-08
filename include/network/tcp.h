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

    virtual int establishServer();
    virtual int checkCity(std::string);
    virtual int getClientId();
    virtual int getCurrPlayer();
    virtual void getMessages(char *);
    TCPNetwork(std::string file="./serverlist");
    virtual ~TCPNetwork();
};

#endif
