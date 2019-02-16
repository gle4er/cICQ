#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void ConnectClient(int Port)
{
    char conn_first[] = "Connection. Wait second player.";
    char conn_second[] = "Connection. You second player.";
    //trune struct
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(Port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int fd_listen = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if(setsockopt(fd_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        perror("Setsockopt");

    int sock_fd[2] = {0, 0};
    int check[1] = {1};
    //connect

    bind(fd_listen, (struct sockaddr*)&addr, sizeof(addr));
    listen(fd_listen, 5);

    sock_fd[0] = accept(fd_listen, NULL, NULL);
    send(sock_fd[0], conn_first, sizeof(conn_first), 0);
    printf("First player connect. Wait second\n");

    sock_fd[1] = accept(fd_listen, NULL, NULL);
    send(sock_fd[1], conn_second, sizeof(conn_second), 0);
    printf("All ok\n\n");

    send(sock_fd[0], check, sizeof(check), 0);
    send(sock_fd[1], check, sizeof(check), 0);

    shutdown(*sock_fd, 0);
    shutdown(fd_listen, 0);
}


int main()
{
    ConnectClient(5000);
    return 0;
}
