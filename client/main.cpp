#include <iostream>

#include "client.h"
#include "interface/console.h"
#include "network/tcp.h"

int main()
{
    new Client(new Console(), new TCPNetwork());

    return 0;
}
