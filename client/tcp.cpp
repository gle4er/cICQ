#include "network/tcp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

bool TCPNetwork::checkCity(std::string city)
{
    bool checkFlag = false;
    send(this->sock_fd, city.c_str(), sizeof(char) * city.length(), 0);
    recv(this->sock_fd, &checkFlag, sizeof(bool), 0);
    return checkFlag;
}

Network::msgType TCPNetwork::getMessages(char *buff)
{
    recv(this->sock_fd, buff, sizeof(char) * 255, 0);
    msgType type = (msgType) buff[0];
    memcpy(buff, buff + 1, 254);
    return type;
}

int TCPNetwork::establishServer(std::string ip, int port)
{
	struct sockaddr_in client_addr;

	this->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = htonl(*ip.c_str());
	return connect(this->sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
}

int TCPNetwork::setClientId()
{
    int id = -1;
    recv(this->sock_fd, &id, sizeof(id), 0);
    return id;
}

TCPNetwork::~TCPNetwork()
{
	shutdown(this->sock_fd, 0);
}
