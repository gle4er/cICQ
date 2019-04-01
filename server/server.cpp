#include "server.h"
#include "logPlay.h"


int Server::ConnectClient(int Port)
{
    char buf[10];
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
    sock_fd = accept(fd_listen, NULL, NULL);
    std::cout << sock_fd << std::endl;
    buf[0] = (char)fd_listen;
    send(sock_fd, buf, sizeof(buf), 0);

    shutdown(sock_fd, 0);
    shutdown(fd_listen, 0);

    return fd_listen;
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
                if(tmp != it)
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

Server::Server()
{
    int count = 0;
    /* Until all players are connected
     * */
    while(count <= MAX_PLAYERS){
        roomPlayers.push_back(ConnectClient(5000));
        count++;
    }
    //    printf("\n\n");
    //    for(int i = 0; i < roomPlayers.size(); i++){
    //        std::cout << roomPlayers[i] << std::endl;
    //    }
}
