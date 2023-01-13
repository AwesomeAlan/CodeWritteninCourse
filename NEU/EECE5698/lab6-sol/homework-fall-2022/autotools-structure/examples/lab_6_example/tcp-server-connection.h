/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

/**
 * @file tcp-server-connection.h
 * @author Filippo Campagnaro
 * @version 1.0.0
 * @brief Socket TCP server class.
 */

#ifndef H_TCP_SERVER_CONN
#define H_TCP_SERVER_CONN

#include "ethernet-connector.h"
#include "service.h"
#include <vector>
#include <memory>

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

  /**
   * Class destructor.
   */
  virtual ~TcpServerConnection();

  /**
   * Accept a new connection and store the IP.
   * @return false if accept fails
   */
  bool acceptConn() override;

  /**
   * Print the tcp server to the ostream
   * @param out a ostream
   */
  void print(std::ostream& out) const override;

private:
  int l_sock_fd; /**< listener socket file descriptor */

  std::vector<std::shared_ptr<Service>> services;

  /** counter of the number of connections*/
  size_t connections_count;



  /**
   * Set the socket options and bind.
   * @return false as soon as any of the operations it performs fails
   */
  bool optionsAndBind();

};

#endif /* H_TCP_SERVER_CONN */