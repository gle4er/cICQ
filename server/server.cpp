#include "server.h"
#include "logPlay.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
    buf[0] = (char)fd_listen;
    printf("%d\n", fd_listen);
    send(sock_fd, buf, sizeof(buf), 0);

    shutdown(sock_fd, 0);
    shutdown(fd_listen, 0);

    return fd_listen;
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
    printf("\n\n");
    for(int i = 0; i < roomPlayers.size(); i++){
        std::cout << roomPlayers[i] << std::endl;
    }
}
