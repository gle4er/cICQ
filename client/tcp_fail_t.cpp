#include "network/tcp_fail_t.h"

#include <string>
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
        if (!send(this->sock_fd, buffer, length, flags)) {
            perror("Cannot connect to any server");
            exit(EXIT_FAILURE);
        }
        return 1;
    }
    return 0;
}

int TCP_Fail_Tolerance::ackRecv(void *buffer, size_t length, int flags)
{
    size_t recvCount = recv(this->sock_fd, buffer, length, flags);
    if (recvCount == 0) {
        if (this->reconnect() != 0) {
            perror("Cannot connect to any server");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < length; i++) {
            char *byte = (char *)buffer + i;
            *byte = 0;
        }
        return 1;
    }
    return 0;
}

int TCP_Fail_Tolerance::checkCity(std::string city)
{
    int checkFlag = 0;
    int send_switched = ackSend(city.c_str(), sizeof(char) * 255, 0);
    int recv_switched = ackRecv(&checkFlag, sizeof(checkFlag), 0);
    if (send_switched || recv_switched) {
        return this->checkCity(city);
    }
    return checkFlag;
}

int TCP_Fail_Tolerance::getClientId()
{
    char tmp[2];
    ackRecv(tmp, sizeof(tmp), 0);
    this->cliId = (int)tmp[0];
    return this->cliId;
}

int TCP_Fail_Tolerance::getCurrPlayer()
{
    char tmp[2];
    ackRecv(tmp, sizeof(tmp), 0);
    return (int)tmp[0];
}

void TCP_Fail_Tolerance::getMessages(char *buff)
{
    ackRecv(buff, sizeof(char) * 255, 0);
}

int TCP_Fail_Tolerance::reconnect()
{
    if (!establishServer()) {
        if (!send(this->sock_fd, &this->cliId, sizeof(this->cliId), 0)) {
            perror("send cliId");
        }
        return 0;
    }
    return 1;
}
