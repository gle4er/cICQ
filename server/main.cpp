#include <iostream>

#include "server.h"
#include "logPlay.h"

#include <signal.h>

int main(int argc, char **argv)
{
    signal(SIGPIPE, SIG_IGN);
    int clientPort = 5000,
        peerPort = 9000;
    std::string clusterHosts;
    if (argc == 4) {
        clientPort = std::atoi(argv[1]);
        peerPort = std::atoi(argv[2]);
        clusterHosts = argv[3];
    }
    new Server(clientPort, peerPort, clusterHosts);
    return 0;
}
