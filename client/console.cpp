#include "interface/console.h"

#include <iostream>

std::string Console::getInput(bool isNotFirst)
{
    if (isNotFirst && !this->message) {
        std::cout << "This city is was! Try again..." << std::endl;
    }

    std::string input;
    std::cout << "Enter city: ";
    std::getline(std::cin, input);

    if(input[0] == 36)
        this->message = true;
    else
        this->message = false;
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

void Console::printTextMessage(std::string city)
{
    std::cout << "Player choosed city: " << city << std::endl;
}

int Console::getAnswerYesNo(std::string text)
{
    std::cout << text << " ";
    while (1) {
        std::cout << "[Y/n] ";
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == "Y" || answer == "y" ||
                answer == "")
            return 0;
        else if (answer == "N" || answer == "n")
            return -1;
    }
    return -1;
}
