#ifndef TCP_FAIL_T_H
#define TCP_FAIL_T_H

#include "network/tcp.h"
#include <string>

class TCP_Fail_Tolerance : public TCPNetwork
{
public:
    int ackSend(const void *buffer, size_t length, int flags);
    int ackRecv(void *buffer, size_t length, int flags);
    int reconnect();

    virtual int checkCity(std::string);
    virtual int getClientId();
    virtual int getCurrPlayer();
    virtual void getMessages(char *);

    TCP_Fail_Tolerance(std::string file="./serverlist") : TCPNetwork(file) {}
    virtual ~TCP_Fail_Tolerance() {};
};

#endif
