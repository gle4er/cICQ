#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_PLAYERS 2

class Server{
    private:
        int ConnectClient(int Port);
    public:
        Server();
        
        std::vector<int> roomPlayers;
        void sendWord();
};

#endif
