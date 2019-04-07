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

bool Server::chatCheck(char *text)
{
    if (text[0] == '$') {
        std::cout << "Message: " << text << std::endl;
        return true;
    }
    return false;
}

void Server::sendWord()
{
    logPlay playTmp;
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

                char *recvBuff = new char[255];
                recv(it, recvBuff, sizeof(char) * 255, 0);

                if(!chatCheck(recvBuff) && playTmp.check(recvBuff) == true){
                    isRightCity = true;
                    currentPlayer = (currentPlayer + 1) % roomPlayers.size();
                }

                for(int tmp : roomPlayers){
                    if(tmp == it) {
                        int tmpSend = playTmp.mistake;
                        send(it, &tmpSend, sizeof(tmpSend), 0);
                    } else {
                        send(tmp, recvBuff, sizeof(char) * 255, 0);
                    }
                }
                delete[] recvBuff;
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
