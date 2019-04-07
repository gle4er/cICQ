#include <iostream>

#include "client.h"
#include "interface/console.h"
#include "network/tcp.h"

int main(int argc, char **argv)
{
    std::string serverlist = "./serverlist";
    if (argc == 2) {
        serverlist = argv[1];
    }
    new Client(new Console(), new TCPNetwork(serverlist));

    return 0;
}
