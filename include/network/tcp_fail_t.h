#ifndef TCP_FAIL_T_H 
#define TCP_FAIL_T_H 

#include "network/tcp.h"
#include <string>

class TCP_Fail_Tolerance : public TCPNetwork {
public:
    int ackSend(const void *buffer, size_t length, int flags);
    int ackRecv(void *buffer, size_t length, int flags);

    int checkCity(std::string);
    int getClientId();
    void getMessages(char *);
    TCP_Fail_Tolerance() : 
        TCPNetwork::TCPNetwork() {}
    TCP_Fail_Tolerance(std::string ses) :
        TCPNetwork::TCPNetwork(ses) {}
};

#endif
