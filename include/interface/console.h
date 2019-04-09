#ifndef CONSOLE_H
#define CONSOLE_H

#include "interface/interface.h"

class Console : public Interface
{
public:
    std::string getInput();
    void printMistake(int mist);
    void printError(std::string);
    void printInfo(std::string);
    void printTextMessage(std::string);
    int getAnswerYesNo(std::string);
};

#endif
