#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <iostream>

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_PLAYERS 3

class Server{
    private:
        void ConnectClient(int Port);
        bool chatCheck(char *city);
    public:
        Server(int clientPort, int peerPort, std::string clusterHosts);
        
        std::vector<int> roomPlayers;
        void sendWord();
        void setNumber();
};

#endif
