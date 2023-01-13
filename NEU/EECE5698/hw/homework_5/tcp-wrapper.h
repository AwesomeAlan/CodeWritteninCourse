/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Kumar Nithyakumar 
*/


#ifndef H_CHAT_SERVER
#define H_CHAT_SERVER

#include <string>
#include <socket-wrapper.h>

/**
 * Class TcpWrapper
 */
class TcpWrapper : public SocketWrapper
{
public:
  /**
   * Class constructor.
   * @param port_num integer with the port number
   */
  TcpWrapper(int port_num);

  /**
   * Class destructor.
   */
  ~TcpWrapper();

  /**
   * Accept a new connection and store the IP.
   * @return false if accept fails
   */
  bool acceptClient();

  /**
   * Receives data from remote host.
   * @param buf buffer where the received data is stored
   * @return number of bytes received (-1 if error occurred)
   */
  int recvData(char* buf) override;

  /**
   * Send data to remote host.
   * @param buf pointer to the buffer where the data to be sent is stored
   * @param size_to_tx size to transmit
   * @return number of bytes sent (-1 if error occurred)
   */
  int sendData(const char* buf, size_t size_to_tx) override;

  /**
   * Function executed in a thread dispatched by the constructor 
   * to start the server listener
   */
  void runServer() override;

protected:
  /**
   * Print something about the socket
   * @param out an ostream to print to
   * @return an ostream
   */
  void print(std::ostream& out) const override;

private:
  int m_port; /**< listen socket port number */
  std::string m_ip; /**< address of who is connected */
  bool m_exit; /**< true if run should end */
  int m_l_sock_fd; /**< listener socket file descriptor */
  int m_sock_fd; /**< data socket file descriptor */
 
  /**
   * Set the socket options and bind.
   * @return false as soon as any of the operations it performs fails
   */
  bool optionsAndBind();

  /**
   * Function called by the destructor to close the sockets
   */
  void quit();

};

#endif /* CHAT_SERVER */
