#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

class Interface {
public:
    virtual std::string getInput(bool isFirst) = 0;
};

#endif
