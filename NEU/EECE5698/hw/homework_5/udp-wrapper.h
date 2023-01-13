#ifndef UDPWRAPPER
#define UDPWRAPPER

#include <string>
#include <socket-wrapper.h>
#include <netinet/in.h>

class UdpWrapper : public SocketWrapper
{
public:
    UdpWrapper(int port_num);
    ~UdpWrapper();
    bool acceptClient();
    int recvData(char* buf);
    int sendData(const char* buf, size_t size_to_tx);
    void runServer();

private:
    int m_port;
    struct sockaddr_in m_last_recv_ip;
    bool m_exit;
    int m_sock_fd;

    bool optionsAndBind();
    void quit();

    protected:
    void print(std::ostream& out) const override;
    std::string getLastIp() const;
};

#endif