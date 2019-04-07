#include "client.h"
#include <iostream>

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

int Client::connect()
{
    for (int retries = 0; retries < 5; retries++) {
        if (retries > 1) {
            interface->printInfo("Retry to connect");
        }
        for (auto &currentServer : serverList) {
            std::string addr = currentServer.ip + ":" + 
                std::to_string(currentServer.port);

            interface->printInfo("Connecting to server");
            if (network->establishServer(currentServer.ip, currentServer.port)) {
                std::string errMsg = "Something went wrong: " + addr;
                interface->printError(errMsg);
                std::perror("Establish connect to server");
                interface->printError("");
            } else {
                std::string msg = "Connect successfull: " + addr;
                interface->printInfo(msg);
                return 0;
            }
        }
    }
    return -1;
}

void Client::waitForAll()
{
    this->clientId = network->getClientId();
}

void Client::enterCity()
{
    std::string input;
    int mistake = 0;
    do {
        if (mistake > 0) {
            interface->printMistake(mistake);
        }
        input = interface->getInput();
    } while ((mistake = network->checkCity(input)) != 0 || input[0] == '$');
}

void Client::waitForMove(int currPlayer)
{
    char *buff = new char[255];
    network->getMessages(buff);
    std::string text(buff);
    if (text[0] == '$') {
        text = "Player " + std::to_string(currPlayer) + " say: " + text.substr(1);
    } else {
        text = "Player choosed city: " + text;
    }
    interface->printTextMessage(text);
}

Client::Client(Interface *iface, Network *netw) : interface(iface), network(netw)
{
    loadServers("./serverlist");
    while (connect()) {
        interface->printError("Cannot connect to one server!");
        int answer = interface->getAnswerYesNo("Retry connect or quit?");
        if (answer == -1)
            exit(EXIT_FAILURE);
    }

    waitForAll();

    int prevPlayer = -1;
    while (1) {
        int currPlayer = network->getCurrPlayer();
        if (prevPlayer != currPlayer) {
            std::cout << "Curr move id: " << currPlayer << " Curr id: " << this->clientId << std::endl;
        }

        if (currPlayer == this->clientId) {
            enterCity();
        } else {
            waitForMove(currPlayer);
        }
        prevPlayer = currPlayer;
    }
}
