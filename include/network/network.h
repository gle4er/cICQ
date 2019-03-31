#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network {
public:
    virtual bool checkCity(std::string) = 0;
    virtual int establishServer(std::string, int) = 0;
};

#endif
