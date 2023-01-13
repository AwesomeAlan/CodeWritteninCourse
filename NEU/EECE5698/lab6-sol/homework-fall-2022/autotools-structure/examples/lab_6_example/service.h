/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

/**
 * @file service.h
 * @author Filippo Campagnaro
 * @version 1.0.0
 * @brief Class that serves a client.
 */

#ifndef H_SERVICE
#define H_SERVICE

#include <ethernet-connector.h>
#include <thread>

/**
 * class Service containing the parameters to be configured
 */
class Service
{
public:
    
  /**
   * Class constructor.
   * @param sk_fd socket file descriptor
   */
  Service(int sk_fd);

  /**
   * Class destructor.
   */
  virtual ~Service();


  /**
   * Method that serves the client by receiving a file of size FILE_SIZE
   */
  void run();

  /**
   * get the status report back to the connected client
   * @return a string describing the status of the reception
   */
  std::string getReport() const;

  /**
   * get the socket file descriptor
   * @return the socket file descriptor
   */
  int getSockFd() const;

private:

  static const unsigned int FILE_SIZE; /**<maximum number of requests */

  int sock_fd; /**<socket file descriptor where the client is already connected*/
  unsigned int total_received_size; /**<number of bytes successful received*/
  std::thread servent_daemon; /**<thread running the servent tasks*/

};


#endif /* H_SERVICE */