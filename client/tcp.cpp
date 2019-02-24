#include "network/tcp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

bool checkCity(std::string city)
{
    return true;
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

TCPNetwork::~TCPNetwork()
{
	shutdown(this->sock_fd, 0);
}
