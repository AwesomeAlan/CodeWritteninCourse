/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

/**
 * @file tcp-client-fwd.h
 * @author Filippo Campagnaro
 * @version 1.0.0
 * @brief Socket TCP server class.
 */

#ifndef H_TCP_CLIENT_FWD
#define H_TCP_CLIENT_FWD

#include "ethernet-connector.h"
#include <memory>

/**
 * Class TcpClientForwarder that forwards data from a socket to another socket
 */
class TcpClientForwarder : public EthConn
{
public:
  /**
   * Class constructor.
   * @param ip_addr string containing the human readable IP address in IPv4
   * of the server to connect to receive the data 
   * @param port_num integer with the port number of the server to connect 
   * to receive the data 
   */
  TcpClientForwarder(const std::string& ip_addr, int port_num);

  /**
   * Class destructor.
   */
  virtual ~TcpClientForwarder();

  /**
   * Connect to the server at the socket ip:port passed at constructor.
   * @return false if connect fails
   */
  bool connectToServer();

  /**
   * Receive data from the connected server.
   * @param buf pointer to the buffer where the received data is stored
   * @return number of bytes received (-1 if error occurred)
   */
  int receive(std::shared_ptr<std::array<char,MTU>> buf) override;

  /**
   * Send data to the connected server.
   * @param buf pointer to the buffer where the data to be sent is stored
   * @param size_to_tx size to transmit
   * @return number of bytes sent (-1 if error occurred)
   */
  int transmit(std::shared_ptr<std::array<char,MTU>> buf, 
    size_t size_to_tx) override;

  /**
   * Forward data receved from the connected server to the 
   * forward_to connection for a certain number of times
   * @param num_times number of times to forward the data
   */
  bool forwardCycle(size_t num_times);

  /**
   * Set the forward_to variable, that contains the connection to the server
   * where the data received in the forwardCycle is transmitted
   * @forwarder out a ostream
   */
  // Exercise 2a: uncomment this line
  void setForwarder(std::shared_ptr<EthConn> forwarder);

protected:
  void print (std::ostream& out) override;

private:
  int sock_fd; /**< socket file descriptor */

  // Exercise 1: declare the forward_to member variable, which is a (decide whether smart or not) 
  // pointer to EthConn that will be set by the setForwarder method (to be implemented as well)
  std::weak_ptr<EthConn> forward_to;
};

#endif /* H_TCP_CLIENT_FORWARDER */
