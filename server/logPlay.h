#ifndef LOGPLAY_H
#define LOGPLAY_H

#include <string>
#include <unordered_set>
#include <fstream>

class logPlay{
    private:
        char lastLetter;
        bool checkLetter(std::string);
        bool isCityPresent(std::string);
        bool isCityExist(std::string);
        std::unordered_set<std::string> enteredCities;
        std::unordered_set<std::string> citiesVocabulaty;
        int mistake;

    public:
        logPlay();
        void insertCity(std::string city);
        bool check(char *tmp);
        void printCities();
        int getMistake();
        int getLastLetter();
};

#endif
