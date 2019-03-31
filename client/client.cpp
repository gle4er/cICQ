#include "client.h"

void Client::loadServers(std::string file)
{
    std::string line;
 
    std::ifstream in(file);
    if (in.is_open()) {
        std::string tmp_line;
        while (getline(in, line)) {
            std::size_t pos = line.find(":");
            std::string ip = line.substr (0, pos);  
            std::string port = line.substr (pos + 1, line.length() - 1);
            serverList.push_back({ip, stoi(port)});
        }
    }
    in.close();
}

void Client::connect()
{
    for (int retries = 0; retries < (int)serverList.size(); retries++) {
        currentServerId = (currentServerId + 1) % serverList.size();
        Server currentServer = serverList[currentServerId];

        std::string addr = currentServer.ip + ":" + 
            std::to_string(currentServer.port);

        interface->printInfo("Connecting to server");
        if (network->establishServer(currentServer.ip, currentServer.port)) {
            std::string errMsg = "Something went wrong: " + addr;
            interface->printError(errMsg);
        } else {
            std::string msg = "Connect successfull: " + addr;
            interface->printInfo(msg);
            break;
        }
    }
}

void Client::waitForAll()
{
    this->clientId = network->setClientId();
}

void Client::enterCity()
{
    std::string input;
    int countOfTryes = 0;
    do {
        input = interface->getInput(countOfTryes > 0);
        countOfTryes++;
    } while (network->checkCity(input));
}

int Client::waitForMove()
{
    char *buff = new char[255];
    Network::msgType type;
    do { 
        type = network->getMessages(buff);
        if (type == Network::MESSAGE) {
            interface->printCity(buff);
        }
    } while (type != Network::CHANGE_CLI_ID);
    int currentClient = std::stoi(buff);
    delete[] buff;
    return currentClient;
}

Client::Client(Interface *iface, Network *netw) : interface(iface), network(netw)
{
    loadServers("./serverlist");
    connect();
    waitForAll();

    int currentClient = 0;
    while (1) {
        if (currentClient == this->clientId) {
            enterCity();
        } else {
            currentClient = waitForMove();
        }
    }
}
