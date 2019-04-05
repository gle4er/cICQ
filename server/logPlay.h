#ifndef LOGPLAY_H
#define LOGPLAY_H

#include <iostream>
#include <map>
#include <array>
#include <string>
#include <unordered_set>

#include <string.h>

class logPlay{
    private:
        char lastLetter;
        bool checkLetter();
        bool checkCorrect();

    public:
        logPlay();
        
        std::string word;
        std::unordered_set<std::string> vocab;
        bool check(char *tmp);
        void printVocab();
};

#endif
