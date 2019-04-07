#ifndef LOGPLAY_H
#define LOGPLAY_H

#include <string>
#include <unordered_set>

class logPlay{
    private:
        char lastLetter;
        bool checkLetter(std::string);
        bool isCityPresent(std::string);
        std::unordered_set<std::string> enteredCities;

    public:
        logPlay() { }
        
        bool check(char *tmp);
        void printCities();
        int mistake;
};

#endif
