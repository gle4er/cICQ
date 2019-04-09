#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network
{
public:
    virtual int establishServer() = 0;
    virtual int checkCity(std::string city) = 0;                    // returns 0, if city is correct
    virtual int getClientId() = 0;                                  // need for set clientId and waiting for all
    virtual int getCurrPlayer() = 0;                                // which this client can handle: who move?
    virtual void getMessages(char *) = 0;                           // get message (or city) or next clientId
    virtual ~Network() {};                                          // close connect
};

#endif
