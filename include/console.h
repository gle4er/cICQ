#ifndef CONSOLE_H
#define CONSOLE_H

#include "interface.h"

class Console : public Interface {
public:
    std::string getInput(bool isFirst);
};

#endif
