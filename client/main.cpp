#include <iostream>

#include "client.h"
#include "interface/console.h"
#include "network/fake_network.h"

int main()
{
    new Client(new Console(), new FakeNetwork());

    return 0;
}
