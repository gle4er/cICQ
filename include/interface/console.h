#ifndef CONSOLE_H
#define CONSOLE_H

#include "interface/interface.h"

class Console : public Interface {
private:
    bool message = false;
public:
    std::string getInput(bool);
    void printError(std::string);
    void printInfo(std::string);
    void printTextMessage(std::string);
    int getAnswerYesNo(std::string);
};

#endif
