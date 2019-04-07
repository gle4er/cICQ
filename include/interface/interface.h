#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

class Interface {
public:
    virtual std::string getInput(bool isFirst) = 0;
    virtual void printMistake(int mist) = 0;
    virtual void printError(std::string) = 0;
    virtual void printInfo(std::string) = 0;
    virtual void printTextMessage(std::string) = 0;
    virtual int getAnswerYesNo(std::string) = 0;
};

#endif
