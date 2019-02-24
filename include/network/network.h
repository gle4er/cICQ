#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network {
public:
    enum msgType { MESSAGE, CHANGE_CLI_ID };

    virtual bool checkCity(std::string city) = 0;                   // returns true, if city is correct
    virtual int establishServer(std::string ip, int port) = 0;      // make connect to the server
    virtual int setClientId() = 0;                                  // need for set clientId and waiting for all
    virtual msgType getMessages(char *) = 0;                        // get message (or city) or next clientId
    virtual ~Network();                                             // close connect
};

#endif
