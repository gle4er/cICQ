#ifndef SERVER_H
#define SERVER_H

#include "logPlay.h"

#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_PLAYERS 2
#define MIN_PORT 9000

class Server{
    private:
        void ConnectClient(int Port);
        void CreateCluster(int Port, std::string ip);
        bool chatCheck(char *city);
        char beSlave();

        bool imMaster = false;
        std::vector<int> roomPlayers;
        int secondServerFD;
        logPlay gameLogic;
    public:
        Server(int clientPort, int peerPort, std::string clusterHosts);
        
        void sendWord(char currentPlayer);
        void setNumber();
};

#endif
