#include "logPlay.h"

bool logPlay::checkLetter()
{
    if(this->lastLetter == word[0])
        return true;
    return false;
}

bool logPlay::checkCorrect()
{
    if(vocab.find(this->word) == vocab.end())
        return false;
    return true;
}

void logPlay::printVocab()
{
    std::unordered_set<std::string> :: iterator itr;
    for(itr = vocab.begin(); itr != vocab.end(); itr++){
        std::cout << (*itr) << std::endl;
    }
}

bool logPlay::check(char tmp[255])
{
    word = std::string(tmp);
//    std::cout << this->word << std::endl;
    if(checkLetter() == false){
        // Return what incorrect word
        std::cout << "Incorrect first letter" << std::endl;
        return false;
    }
    if(checkCorrect() == false){
        std::cout << "Incorrect word" << std::endl;
        return false;
    }

    this->lastLetter = word[word.length() - 1];
    return true;
}

logPlay::logPlay()
{
    this->lastLetter = 'a';
    vocab.insert("Irkutsk");
    vocab.insert("Moskow");
    std::cout << "Hi" << std::endl;
}
