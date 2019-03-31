#include "interface/console.h"

#include <iostream>

std::string Console::getInput(bool isNotFirst)
{
    if (isNotFirst) {
        std::cout << "This city is was! Try again..." << std::endl;
    }

    std::string input;
    std::cout << "Enter city: ";
    std::cin >> input;

    return input;
}

void Console::printError(std::string error)
{
    std::cout << error << std::endl;
}

void Console::printInfo(std::string msg)
{
    std::cout << msg << std::endl;
}
