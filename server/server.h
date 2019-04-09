#ifndef SERVER_H
#define SERVER_H

#include "logPlay.h"

#include <vector>
#include <string>

#define MAX_PLAYERS 2
#define MIN_PORT 9000

class Server
{
private:
    void ConnectClient(int fd_listen);
    void CreateCluster(int Port, std::string ip);
    int initClientPort(int Port);
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
