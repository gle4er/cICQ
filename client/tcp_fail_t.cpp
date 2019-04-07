#include "network/tcp_fail_t.h" 

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int TCP_Fail_Tolerance::ackSend(const void *buffer, size_t length, int flags)
{
    size_t sndCount = send(this->sock_fd, buffer, length, flags);
    if (sndCount == 0) {
        if (this->establishServer() != 0) {
            perror("Cannot connect to any server");
            exit(EXIT_FAILURE);
        }
        sndCount = send(this->sock_fd, buffer, length, flags);
    }
    return sndCount;
}

int TCP_Fail_Tolerance::ackRecv(void *buffer, size_t length, int flags)
{
    size_t recvCount = recv(this->sock_fd, buffer, length, flags);
    if (recvCount == 0) {
        if (this->establishServer() != 0) {
            perror("Cannot connect to any server");
            exit(EXIT_FAILURE);
        }
        recvCount = recv(this->sock_fd, buffer, length, flags);
    }
    return 0;
}

bool TCP_Fail_Tolerance::checkCity(std::string city)
{
    bool checkFlag = false;
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

