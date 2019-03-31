#include "client.h"

void Client::loadServers(std::string file)
{
    serverList.push_back({"127.0.0.1", 228});
    return;
}

std::string Client::getInput()
{
    std::string input;
    int countOfTryes = 0;
    do {
        input = interface->getInput(countOfTryes > 0);
        countOfTryes++;
    } while (network->checkCity(input));

    return input;
}

void Client::connect()
{
    for (int retries = 0; retries < (int)serverList.size(); retries++) {
        currentServerId = (currentServerId + 1) % serverList.size();
        Server currentServer = serverList[currentServerId];

        std::string addr = currentServer.ip + ":" + 
            std::to_string(currentServer.port);

        if (network->establishServer(currentServer.ip, currentServer.port)) {
            std::string errMsg = "Something went wrong: " + addr;
            interface->printError(errMsg);
        } else {
            std::string msg = "Connetct successfull: " + addr;
            interface->printInfo(msg);
        }
    }
}

Client::Client(Interface *iface, Network *netw) : interface(iface), network(netw)
{
    loadServers("ses");
    connect();

    while (1) {
        this->getInput();
    }
}
