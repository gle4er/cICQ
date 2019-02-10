#include "console.h"

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
