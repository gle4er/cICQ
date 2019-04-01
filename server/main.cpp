#include <iostream>

#include "server.h"
#include "logPlay.h"

int main()
{
    Server *tmp = new Server();
    tmp->sendWord();
//    logPlay *tmp = new logPlay();
    
//    tmp->check("Archangel");

    return 0;
}
