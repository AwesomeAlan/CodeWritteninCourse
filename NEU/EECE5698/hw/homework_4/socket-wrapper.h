#ifndef H_SOCKET_WRAPPER
#define H_SPCKET_WRAPPER

#include <string>
#include <iostream>

class SocketWrapper{

public:
    virtual ~SocketWrapper(){};
    virtual int recvData(char* buf) = 0;
    virtual int sendData(const char* buf, size_t size_to_tx) = 0;
    virtual void runServer() = 0;
    

protected:
    virtual void print(std::ostream &out) const = 0;
    //exercise 5
    friend std::ostream& operator<<(std::ostream& out, const SocketWrapper& object);

};

std::ostream& operator<<(std::ostream& out , const SocketWrapper& object);

#endif