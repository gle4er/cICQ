#include "game.h"

std::string Game::getInput()
{
    std::string input;
    int countOfTryes = 0;
    do {
        input = interface->getInput(countOfTryes > 0);
        countOfTryes++;
    } while (goodCity(input));

    dictionary[input] = true;

    return input;
}

bool Game::goodCity(std::string input)
{
    return dictionary.find(input) != dictionary.end();
}

Game::Game(Interface *iface) : interface(iface)
{
    while (1) {
        this->getInput();
    }
}
