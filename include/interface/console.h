#ifndef CONSOLE_H
#define CONSOLE_H

#include "interface/interface.h"

class Console : public Interface {
public:
    std::string getInput(bool);
    void printError(std::string);
    void printInfo(std::string);
};

#endif