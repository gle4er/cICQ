#include "client.h"

void Client::loadServers(std::string file)
{
    std::string line;
 
    std::ifstream in(file);
    if (in.is_open())
    {
        int i = 0;
        std::string tmp_line;
        while (getline(in, line))
        {
            std::stringstream ss(line);
            while(getline(ss, line, ':')){
                i++;
                if (i % 2)
                    (tmp_line = line);
                else {
                    serverList.push_back({tmp_line, std::stoi(line)});
                    std::cout << tmp_line << "  :  "<< line << std::endl;
                }
            }
        }
    }
    in.close();
    return;
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
    /*
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
    */
}
