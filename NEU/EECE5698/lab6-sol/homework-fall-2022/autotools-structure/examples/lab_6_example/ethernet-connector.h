/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

/**
 * @file ethernet-connector.h
 * @author Filippo Campagnaro
 * @version 1.0.0
 * @brief Base Ethernet connector.
 */

#ifndef H_ETHERNET_C_FS
#define H_ETHERNET_C_FS

#include <string>
#include <memory>
#include <array>

constexpr size_t MTU = 512; /** Maximum transmission unit*/

/**
 * class EthConn containing the API of an Ethernet connector
 */
class EthConn
{
public:
  /** String with the LOCAL_HOST IPv4 address. */
  static const std::string LOCAL_HOST; 
  
  /**
   * Class constructor.
   * @param ip_addr string containing the human readable IP address in IPv4
   * @param port_num integer with the port number
   */
  EthConn(const std::string& ip_addr, int port_num);

  /**
   * Class constructor.
   * @param port_num integer with the port number
   */
  EthConn(int port_num);

  /**
   * Class destructor.
   */
  virtual ~EthConn() {}


  /**
   * Get the IP address of the last remote host connected.
   * @return the ip address
   */
  inline std::string getIp() const {
    return ip;
  }

  /**
   * Get the socket port number.
   * @return the port number
   */
  inline int getPort() const {
    return port;
  }

  /**
   * Accept a new connection and store the IP.
   * @return false if accept fails
   */
  virtual bool acceptConn() = 0;

  /**
   * Print the connector to the ostream
   * @param out a ostream
   */
  virtual void print(std::ostream& out) const;

protected:
  /** string containing the human readable IP address */
  std::string ip; 
  /** integer with the port number*/
  int port;

};

/**
 * Overloaded operator<< for a EthConn
 * @param out a std::ostream object
 * @param conn reference to the connector to be printed
 * @return the manipulated ostream object
 */
std::ostream& operator<<(std::ostream& out, const EthConn& conn);

#endif /* H_ETHERNET_C_FS */