#include "logPlay.h"
#include <iostream>
#include <algorithm>

bool logPlay::checkLetter(std::string word)
{
    if(this->lastLetter == word[0])
        return true;
    return false;
}

bool logPlay::isCityPresent(std::string word)
{
    if(enteredCities.find(word) == enteredCities.end())
        return false;
    return true;
}

bool logPlay::isCityExist(std::string word)
{
    if(citiesVocabulaty.find(word) == citiesVocabulaty.end())
        return false;
    return true;
}

void logPlay::printCities()
{
    std::unordered_set<std::string> :: iterator itr;
    for(itr = enteredCities.begin(); itr != enteredCities.end(); itr++){
        std::cout << (*itr) << std::endl;
    }
}

bool logPlay::check(char *tmp)
{
    std::string word(tmp);
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    std::cout << "City entered: " << word << std::endl;
    this->mistake = 0;

    if (enteredCities.size() != 0) {
        //    std::cout << this->word << std::endl;
        if(checkLetter(word) == false){
            // Return what incorrect word
            std::cout << "Incorrect first letter" << std::endl;
            this->mistake = 1;
            return false;
        }
        if(isCityPresent(word)){
            std::cout << "This city was" << std::endl;
            this->mistake = 2;
            return false;
        }
    }

    if(!isCityExist(word)){
        std::cout << "This city does not exist" << std::endl;
        this->mistake = 3;
        return false;
    }

//    printVocab();
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

