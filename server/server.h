#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <iostream>

#define MAX_PLAYERS 2

class Server{
    private:
        int ConnectClient(int Port);
    public:
        std::vector<int> roomPlayers;
        Server();
};

#endif
