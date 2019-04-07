#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network {
public:
    virtual int whatMistake() = 0;
    virtual bool checkCity(std::string city) = 0;                   // returns true, if city is correct
    virtual int establishServer(std::string ip, int port) = 0;      // make connect to the server
    virtual int getClientId() = 0;                                  // need for set clientId and waiting for all
    virtual int getCurrPlayer() = 0;                                // which this client can handle: who move?
    virtual void getMessages(char *) = 0;                        // get message (or city) or next clientId
    virtual ~Network() {};                                          // close connect
};

#endif
