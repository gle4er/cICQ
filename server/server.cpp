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

void Server::sendWord()
{
    logPlay *playTmp = new logPlay();
    char buf[255];
    while(1){ //condition ???
        for(int it : roomPlayers){
            std::cout << it << std::endl;
            strcpy(buf, "You move");
            recv(it, buf, sizeof(buf), 0);

            strcpy(buf, (char*)&it); //player walks now
            for(int tmp : roomPlayers){
                recv(tmp, buf, sizeof(buf), 0);
            }

            send(it, buf, sizeof(buf), 0);
            if(playTmp->check(buf) == true){
                for(int tmp : roomPlayers){
                    if(tmp != it)
                        recv(tmp, buf, sizeof(buf), 0);
                }
            }else{
                strcpy(buf, "Bad city, enter another");
                recv(it, buf, sizeof(buf), 0);
            }
        }
    }
}

void Server::getNumber()
{
    std::cout << roomPlayers.size() << std::endl;

    char buf[2];
    int tmp;
    for(int i = 0; i < (int)roomPlayers.size(); i++){
        std::cout << roomPlayers[i] << std::endl;
        buf[0] = (char)(i + 1);
        tmp = roomPlayers[i];
        send(tmp, buf, sizeof(buf), 0);
        perror(NULL);
    }
}

Server::Server()
{
    /* Until all players are connected
     * */
    ConnectClient(5000);

    std::cout << "hi" << std::endl;
    getNumber();
}
