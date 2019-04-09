#include "logPlay.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_set>

bool logPlay::checkLetter(std::string word)
{
    return this->lastLetter == word[0];
}

bool logPlay::isCityPresent(std::string word)
{
    return enteredCities.find(word) != enteredCities.end();
}

bool logPlay::isCityExist(std::string word)
{
    return citiesVocabulaty.find(word) != citiesVocabulaty.end();
}

bool logPlay::check(char *tmp)
{
    std::string word(tmp);
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    std::cout << "City entered: " << word << std::endl;
    this->mistake = 0;

    if (enteredCities.size() != 0) {
        if (!checkLetter(word)) {
            std::cout << "Incorrect first letter" << std::endl;
            this->mistake = 1;
            return false;
        }
        if (isCityPresent(word)) {
            std::cout << "This city was" << std::endl;
            this->mistake = 2;
            return false;
        }
    }

    if (!isCityExist(word)) {
        std::cout << "This city does not exist" << std::endl;
        this->mistake = 3;
        return false;
    }

    insertCity(word);
    std::cout << "Last letter: " << this->lastLetter << std::endl;
    std::cout << "City is correct" << std::endl;
    return true;
}

void logPlay::insertCity(std::string city)
{
    enteredCities.insert(city);
    this->lastLetter = city[city.length() - 1];
}

int logPlay::getMistake()
{
    return this->mistake;
}

logPlay::logPlay()
{
    std::string line;
    std::string file = "./world_cities";

    std::ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)) {
            citiesVocabulaty.insert(line);
        }
    }
    in.close();
}

