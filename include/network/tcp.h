#ifndef TCP_H
#define TCP_H

#include "network/network.h"

class TCPNetwork : public Network {
private:
	int sock_fd;

public:
    bool checkCity(std::string);
    int establishServer(std::string, int);
};

#endif
