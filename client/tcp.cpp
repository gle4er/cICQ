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
	char buf[80];

	this->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = htonl(*ip.c_str());
	connect(this->sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
	printf("%d\n", this->sock_fd);
	
    printf("\n");
	recv(this->sock_fd, buf, sizeof(buf), 0);
	for(int i = 0; i < sizeof(buf); i++)
		printf("%c", buf[i]);
	
    printf("\n");

    int check[1] = {0};
    while(check[0] == 0){
        recv(this->sock_fd, check, sizeof(check), 0);
    }

	shutdown(this->sock_fd, 0);

	return 0;
}
