#include "server.h"
#include "logPlay.h"
#include <arpa/inet.h>
#include <iostream>

void Server::CreateCluster(int Port, std::string serverLine)
{
    if (Port == MIN_PORT) {
        this->imMaster = true;
    }
    if (imMaster) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(Port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        int fd_listen = socket(AF_INET, SOCK_STREAM, 0);
        int opt = 1;
        if (setsockopt(fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
            perror("Setsockopt");

        bind(fd_listen, (struct sockaddr*)&addr, sizeof(addr));
        listen(fd_listen, 5);
        this->secondServerFD = accept(fd_listen, NULL, NULL);
        if (this->secondServerFD == 0) {
            std::cerr << "Failed to connect with slave" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            std::cout << "Connected to slave" << std::endl;
        }
    } else {
        std::size_t pos = serverLine.find(":");
        std::string ip = serverLine.substr(0, pos);  
        std::string port = serverLine.substr(pos + 1);

        struct sockaddr_in client_addr;
        this->secondServerFD = socket(AF_INET, SOCK_STREAM, 0);
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(std::stoi(port));
        client_addr.sin_addr.s_addr = inet_addr(ip.c_str());
        connect(this->secondServerFD, (struct sockaddr*)&client_addr, sizeof(client_addr));
        if (this->secondServerFD == 0) {
            std::cerr << "Failed to connect with master" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            std::cout << "Connected to master" << std::endl;
        }
    }
}

int Server::initClientPort(int Port)
{
    //trune struct
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(Port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int fd_listen = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if(setsockopt(fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        perror("Setsockopt");

    if (bind(fd_listen, (struct sockaddr*)&addr, sizeof(addr)))
        perror("bind");
    if (listen(fd_listen, 5))
        perror("listen");
    return fd_listen;
}

void Server::ConnectClient(int fd_listen)
{
    int count = 0;
    while(count < MAX_PLAYERS){
        int sock_fd = accept(fd_listen, NULL, NULL);
        if (sock_fd == -1)
            perror("accept");
        roomPlayers.push_back(sock_fd);
        count++;
        //    send(sock_fd, &fd_listen, sizeof(fd_listen), 0);
    }
}

bool Server::chatCheck(char *text)
{
    if (text[0] == '$') {
        std::cout << "Message: " << text << std::endl;
        return true;
    }
    return false;
}

char Server::beSlave()
{
    char currentPlayer = 0;
    while (true) {
        if (recv(this->secondServerFD, &currentPlayer, sizeof(currentPlayer), 0) == 0)
            break;
        if (currentPlayer == -1) {
            std::cerr << "Player disconnected, shutdown" << std::endl;
            exit(EXIT_FAILURE);
        }
        bool isRightCity = false;
        if (recv(this->secondServerFD, &isRightCity, sizeof(isRightCity), 0) == 0)
            break;
        if (isRightCity) {
            char *recvBuff = new char[255];
            if (recv(this->secondServerFD, recvBuff, sizeof(char) * 255, 0) == 0)
                break;
            gameLogic.insertCity(recvBuff);
        }
    }
    std::cout << "slave take control" << std::endl;
    return currentPlayer;
}

void Server::sendWord(char currentPlayer)
{
    if (!imMaster) {
        // all Players must reset state
        for (auto &sock : roomPlayers) {
            char sendVal = 0;
            send(sock, &sendVal, sizeof(sendVal), 0);
        }
    }
    bool disconnectedPlayer = false;
    while(1) { //condition ???
        std::cout << "Current player move: " << (int)currentPlayer << std::endl;
        int currSocket = roomPlayers[currentPlayer];

        bool isRightCity = false;
        bool firstAttempt = true;
        while(isRightCity == false){
            //send id walking
            if (disconnectedPlayer) {
                currentPlayer = -1;
            }

            if (imMaster) {
                send(this->secondServerFD, &currentPlayer, sizeof(currentPlayer), 0);
            }

            for (auto &socket : roomPlayers) {
                if (socket != currSocket || firstAttempt) {
                    send(socket, &currentPlayer, sizeof(currentPlayer), 0);
                }
            }

            if (disconnectedPlayer) {
                std::cerr << "Player disconnected, shutdown" << std::endl;
                exit(EXIT_FAILURE);
            }

            firstAttempt = false;

            char *recvBuff = new char[255];
            if (recv(currSocket, recvBuff, sizeof(char) * 255, 0) == 0) {
                disconnectedPlayer = true;
            }

            if(!chatCheck(recvBuff) && gameLogic.check(recvBuff) == true){
                isRightCity = true;
                currentPlayer = (currentPlayer + 1) % roomPlayers.size();
            }

            if (imMaster) {
                send(this->secondServerFD, &isRightCity, sizeof(isRightCity), 0);
                if (isRightCity) {
                    send(this->secondServerFD, recvBuff, sizeof(char) * 255, 0);
                }
            }

            for(int tmp : roomPlayers){
                if(tmp == currSocket) {
                    int tmpSend = gameLogic.getMistake();
                    if (send(currSocket, &tmpSend, sizeof(tmpSend), 0) == 0)
                        disconnectedPlayer = true;
                } else {
                    if (send(tmp, recvBuff, sizeof(char) * 255, 0) == 0)
                        disconnectedPlayer = true;
                }
            }
            delete[] recvBuff;
        }
    }
}

void Server::setNumber()
{
    char buf[2];
    int tmp;
    std::vector<int> playerIds;
    for(int i = 0; i < (int)roomPlayers.size(); i++){
        if (imMaster) {
            buf[0] = (char)i;
            tmp = roomPlayers[i];
            send(tmp, buf, sizeof(buf), 0);
        } else {
            int playerId = 0;
            tmp = roomPlayers[i];
            recv(tmp, &playerId, sizeof(playerId), 0);
            playerIds.push_back(playerId);
        }
    }
    if (!imMaster) {
        std::vector<int> roomTmp(roomPlayers.size());
        for (int i = 0; i < (int)playerIds.size(); i++) {
            int index = playerIds[i];
            roomTmp[index] = roomPlayers[i];
        }
        this->roomPlayers = roomTmp;
    }
}

Server::Server(int clientPort, int peerPort, std::string clusterHosts)
{
    /* Until all players are connected
     * */
    int fd_listen = initClientPort(clientPort);
    CreateCluster(peerPort, clusterHosts);

    char currentPlayer = 0;
    if (!imMaster) {
        currentPlayer = beSlave();
    }

    ConnectClient(fd_listen);

    if (imMaster) {
        std::cout << "master is up" << std::endl;
    }

    setNumber();
    sendWord(currentPlayer);
}
