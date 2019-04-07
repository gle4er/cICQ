#ifndef TCP_H
#define TCP_H

#include "network/network.h"

class TCPNetwork : public Network {
private:
	int sock_fd;

public:
    int checkCity(std::string);
    int establishServer(std::string, int);
    int getClientId();
    int getCurrPlayer();
    void getMessages(char *);
    ~TCPNetwork();
};

#endif
