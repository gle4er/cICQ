#ifndef GAME_H
#define GAME_H

#include "interface.h"

#include <unordered_map>
#include <string>

class Game {
private:
    Interface *interface;
    std::unordered_map<std::string, bool> dictionary;

public:
    bool goodCity(std::string);
    std::string getInput();

    Game(Interface *iface);
};

#endif
