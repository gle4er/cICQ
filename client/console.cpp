#include "interface/console.h"

#include <iostream>

std::string Console::getInput()
{
    std::string input;
    std::cout << "Enter city (or $some_text for messaging): ";
    std::getline(std::cin, input);

    return input;
}

void Console::printMistake(int mist)
{
    if(mist == 1) {
        std::cout << "Wrong first letter. ";
    } else if(mist == 2) {
        std::cout << "This city has already been. ";
    } else if(mist == 3) {
        std::cout << "This city doesn't exists. ";
    }
}

void Console::printError(std::string error)
{
    std::cout << error << std::endl;
}

void Console::printInfo(std::string msg)
{
    std::cout << msg << std::endl;
}

void Console::printTextMessage(std::string text)
{
    std::cout << text << std::endl;
}

int Console::getAnswerYesNo(std::string text)
{
    std::cout << text << " ";
    while (1) {
        std::cout << "[Y/n] ";
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == "Y" || answer == "y" ||
            answer == "") {
            return 0;
        } else if (answer == "N" || answer == "n") {
            return -1;
        }
    }
    return -1;
}
