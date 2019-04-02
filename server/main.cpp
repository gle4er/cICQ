#include <iostream>

#include "server.h"
#include "logPlay.h"

#include <signal.h>

int main()
{
    signal(SIGPIPE, SIG_IGN);
    Server *tmp = new Server();
//    logPlay *tmp = new logPlay();
    
//    tmp->check("Archangel");

    return 0;
}
