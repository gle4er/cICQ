#include "client.h"

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
    } else if (text[0] == '0') {
        return;
    } else {
        text = "Player " + std::to_string(currPlayer) + " choosed city: " + text;
    }
    interface->printTextMessage(text);
}

Client::Client(Interface *iface, Network *netw) : interface(iface), network(netw)
{
    interface->printInfo("Connecting...");
    while (network->establishServer()) {
        interface->printError("Cannot connect to one server!");
        int answer = interface->getAnswerYesNo("Retry connect or quit?");
        if (answer == -1)
            exit(EXIT_FAILURE);
    }
    interface->printInfo("Connected, wait for all");

    waitForAll();

    int prevPlayer = -1;
    while (1) {
        int currPlayer = network->getCurrPlayer();
        if (currPlayer == -1) {
            interface->printError("One of players is disconnected, the game is going down...");
            exit(EXIT_SUCCESS);
        }
        if (prevPlayer != currPlayer) {
            std::string infoMsg = "Curr move id: " + std::to_string(currPlayer) + " Curr id: " + std::to_string(this->clientId);
            interface->printInfo(infoMsg);
        }

        if (currPlayer == this->clientId) {
            enterCity();
        } else {
            waitForMove(currPlayer);
        }
        prevPlayer = currPlayer;
    }
}
