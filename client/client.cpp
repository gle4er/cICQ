#include "client.h"

void Client::waitForAll()
{
    this->clientId = network->getClientId();
}

void Client::enterCity()
{
    std::string input;
    int countOfTryes = 0;
    do {
        input = interface->getInput(countOfTryes > 0);
        countOfTryes++;
    } while (!network->checkCity(input));
}

void Client::waitForMove()
{
    char *buff = new char[255];
    network->getMessages(buff);
    interface->printTextMessage(buff);
}

Client::Client(Interface *iface, Network *netw) : interface(iface), network(netw)
{
    while (network->establishServer()) {
        interface->printError("Cannot connect to one server!");
        int answer = interface->getAnswerYesNo("Retry connect or quit?");
        if (answer == -1)
            exit(EXIT_FAILURE);
    }

    waitForAll();

    while (1) {
        int currPlayer = network->getCurrPlayer();
        std::string infoMsg = "Curr move id: " + std::to_string(currPlayer) + " Curr id: " + std::to_string(this->clientId);
        interface->printInfo(infoMsg);
        if (currPlayer == this->clientId) {
            enterCity();
        } else {
            waitForMove();
        }
    }
}
