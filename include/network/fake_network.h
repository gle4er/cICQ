/*
 * This is for testing purposes only
 */
#ifndef FAKE_NETWORK_H
#define FAKE_NETWORK_H

#include "network/network.h"
#include <unordered_map>

class FakeNetwork : public Network {
private:
    std::unordered_map<std::string, bool> dictionary;

public:
    bool checkCity(std::string);
    int establishServer(std::string, int);
};

#endif
