#include "network/tcp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <fstream>
#include <vector>

#include <iostream>

#include <errno.h>
extern int errno;

int TCPNetwork::checkCity(std::string city)
{
    int checkFlag = 0;
    send(this->sock_fd, city.c_str(), sizeof(char) * 255, 0);
    recv(this->sock_fd, &checkFlag, sizeof(checkFlag), 0);
    return checkFlag;
}

void TCPNetwork::getMessages(char *buff)
{
    recv(this->sock_fd, buff, sizeof(char) * 255, 0);
}

int TCPNetwork::establishServer()
{
    for (int retries = 0; retries < 5; retries++) {
        for (auto &currentServer : serverList) {
            std::string addr = currentServer.ip + ":" + 
                std::to_string(currentServer.port);

            std::cout << addr << std::endl;
            if (this->setSocket(currentServer.ip, currentServer.port) == 0) {
                return 0;
            }
        }
    }
    return -1;
}

int TCPNetwork::setSocket(std::string ip, int port)
{
	struct sockaddr_in client_addr;

	if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        perror("socket");
    int opt = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        perror("Setsockopt");

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    // wait before slave or master be ready
	int rc = connect(this->sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if (rc != 0)
        perror("connect");
    return rc;
}

int TCPNetwork::getClientId()
{
    char tmp[2];
    recv(this->sock_fd, tmp, sizeof(tmp), 0);
    this->cliId = (int)tmp[0];
    return this->cliId;
}

int TCPNetwork::getCurrPlayer()
{
    char tmp[2];
    recv(this->sock_fd, tmp, sizeof(tmp), 0);
    return (int)tmp[0];
}

TCPNetwork::TCPNetwork(std::string file)
{
    std::ifstream in(file);
    if (in.is_open()) {
        std::string tmp_line;
        std::string line;
        while (getline(in, line)) {
            std::size_t pos = line.find(":");
            std::string ip = line.substr (0, pos);  
            std::string port = line.substr (pos + 1, line.length() - 1);
            serverList.push_back({ip, stoi(port)});
        }
    }
    in.close();
}

TCPNetwork::~TCPNetwork()
{
	shutdown(this->sock_fd, 0);
}
