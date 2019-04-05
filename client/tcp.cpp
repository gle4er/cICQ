#include "network/tcp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <iostream>
bool TCPNetwork::checkCity(std::string city)
{
    bool checkFlag = false;
    send(this->sock_fd, city.c_str(), sizeof(char) * 255, 0);
    recv(this->sock_fd, &checkFlag, sizeof(checkFlag), 0);
    return checkFlag;
}

void TCPNetwork::getMessages(char *buff)
{
    recv(this->sock_fd, buff, sizeof(char) * 255, 0);
}

int TCPNetwork::establishServer(std::string ip, int port)
{
	struct sockaddr_in client_addr;

	this->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	return connect(this->sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
}

int TCPNetwork::getClientId()
{
    char tmp[2];
    recv(this->sock_fd, tmp, sizeof(tmp), 0);
    int id = (int)tmp[0];
    return id;
}

int TCPNetwork::getCurrPlayer()
{
    return this->getClientId();
}

TCPNetwork::~TCPNetwork()
{
	shutdown(this->sock_fd, 0);
}
