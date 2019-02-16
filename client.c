#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	struct sockaddr_in client_addr;
	char buf[80];

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(5000);
	client_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(sock_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));
	printf("%d\n", sock_fd);
	
    printf("\n");
	recv(sock_fd, buf, sizeof(buf), 0);
	for(int i = 0; i < sizeof(buf); i++)
		printf("%c", buf[i]);
	
    printf("\n");

    int check[1] = {0};
    while(check[0] == 0){
        recv(sock_fd, check, sizeof(check), 0);
    }

	shutdown(sock_fd, 0);

	return 0;
}
