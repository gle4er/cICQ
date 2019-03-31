#include "network/fake_network.h"

bool FakeNetwork::checkCity(std::string city)
{
    if (dictionary.find(city) != dictionary.end()) {
        dictionary[city] = true;
        return true;
    }
    return false;
}

int FakeNetwork::establishServer(std::string ip, int port)
{
    return 0;
}
