#include "server.h"
#include "logPlay.h"

#include <unistd.h>

void Server::ConnectClient(int Port)
{
    //trune struct
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(Port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int fd_listen = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if(setsockopt(fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        perror("Setsockopt");

    bind(fd_listen, (struct sockaddr*)&addr, sizeof(addr));
    listen(fd_listen, 5);

    int sock_fd;
    int count = 1;
    while(count < MAX_PLAYERS){
        sock_fd = accept(fd_listen, NULL, NULL);
        roomPlayers.push_back(sock_fd);
        count++;
        //    send(sock_fd, &fd_listen, sizeof(fd_listen), 0);
    }
}

bool Server::chatCheck(char *city)
{
    if(city[0] == 36){
        std::cout << "Message: " << city << std::endl;
        return true;
    }
    return false;
}

void Server::sendWord()
{
    logPlay *playTmp = new logPlay();
    char currentPlayer = 0;
    while(1){ //condition ???
        for(int it : roomPlayers){
            std::cout << "Current player mover: " << it << std::endl;

            bool isRightCity = false;
            bool firstAttempt = true;
            while(isRightCity == false){
                //send id walking
                for(auto &socket : roomPlayers){
                    if (socket != it || firstAttempt) {
                        send(socket, &currentPlayer, sizeof(currentPlayer), 0);
                    }
                }
                firstAttempt = false;

                char *city = new char[255];
                recv(it, city, sizeof(char) * 255, 0);

                if(!chatCheck(city)){
                    if(playTmp->check(city) == true){
                        isRightCity = true;
                        currentPlayer = (currentPlayer + 1) % roomPlayers.size();
                    }
                }
                for(int tmp : roomPlayers){
                    if(tmp != it)
                        send(tmp, city, sizeof(char) * 255, 0);
                }
                send(it, &isRightCity, sizeof(isRightCity), 0);
                delete[] city;
            }
        }
    }
}

void Server::setNumber()
{
    char buf[2];
    int tmp;
    for(int i = 0; i < (int)roomPlayers.size(); i++){
        buf[0] = (char)i;
        tmp = roomPlayers[i];
        send(tmp, buf, sizeof(buf), 0);
    }
}

Server::Server()
{
    /* Until all players are connected
     * */
    ConnectClient(5000);

    std::cout << "hi" << std::endl;
    setNumber();
    sendWord();
}
