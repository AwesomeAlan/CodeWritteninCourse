/* 
 * [2022] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */


#ifndef H_TCP_SERVER_CONN
#define H_TCP_SERVER_CONN

#include "ethernet-connector.h"



/**
 * Class TcpServerConnection
 */
class TcpServerConnection : public EthConn
{
public:
  /**
   * Class constructor.
   * @param port_num integer with the port number
   */
  TcpServerConnection(int port_num);

  // Exercise 4: declare and implement the destructor
  virtual ~TcpServerConnection();
  /**
   * Accept a new connection and store the IP.
   * @return false if accept fails
   */
  bool acceptConn();

  /**
   * Receive data from remote host.
   * @param buf pointer to the buffer where the received data is stored
   * @return number of bytes received (-1 if error occurred)
   */
  int receive(std::shared_ptr<std::array<char,MTU>> buf) override;

  /**
   * Send data to remote host.
   * @param buf pointer to the buffer where the data to be sent is stored
   * @param size_to_tx size to transmit
   * @return number of bytes sent (-1 if error occurred)
   */
  int transmit(std::shared_ptr<std::array<char,MTU>> buf, 
    size_t size_to_tx) override;

  // Exercise 1: declare and implement the print() method that overrides print() in EthConn
  void print(std::ostream& out) const override;
  
private:
  int l_sock_fd; /**< listener socket file descriptor */
  int sock_fd; /**< data socket file descriptor */

  /** counter of the number of connections*/
  size_t connections_count;

  /**
   * Set the socket options and bind.
   * @return false as soon as any of the operations it performs fails
   */
  bool optionsAndBind();

};

#endif /* H_TCP_SERVER_CONN */