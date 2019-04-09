#include "network/tcp_fail_t.h" 

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

int TCP_Fail_Tolerance::ackSend(const void *buffer, size_t length, int flags)
{
    size_t sndCount = send(this->sock_fd, buffer, length, flags);
    if (sndCount == 0) {
        if (this->reconnect() != 0) {
            perror("Cannot connect to any server");
            exit(EXIT_FAILURE);
        } else {
            std::cerr << "Switched to slave" << std::endl;
        }
        sndCount = send(this->sock_fd, buffer, length, flags);
    }
    return sndCount;
}

int TCP_Fail_Tolerance::ackRecv(void *buffer, size_t length, int flags)
{
    size_t recvCount = recv(this->sock_fd, buffer, length, flags);
    if (recvCount == 0) {
        if (this->reconnect() != 0) {
            perror("Cannot connect to any server");
            exit(EXIT_FAILURE);
        } else {
            std::cerr << "Switched to slave" << std::endl;
        }
        recvCount = recv(this->sock_fd, buffer, length, flags);
    }
    return recvCount;
}

int TCP_Fail_Tolerance::checkCity(std::string city)
{
    int checkFlag = 0;
    ackSend(city.c_str(), sizeof(char) * 255, 0);
    ackRecv(&checkFlag, sizeof(checkFlag), 0);
    return checkFlag;
}

int TCP_Fail_Tolerance::getClientId()
{
    char tmp[2];
    ackRecv(tmp, sizeof(tmp), 0);
    int id = (int)tmp[0];
    return id;
}

void TCP_Fail_Tolerance::getMessages(char *buff)
{
    ackRecv(buff, sizeof(char) * 255, 0);
}

int TCP_Fail_Tolerance::reconnect()
{
    if (!establishServer()) {
        int rc = send(this->sock_fd, &clientId, sizeof(clientId), 0);
        perror("send");
        if (rc > 0)
            return 0;
    }
    return 1;
}
