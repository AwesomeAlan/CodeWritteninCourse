/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <tcp-wrapper.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

TcpWrapper::TcpWrapper(int port_num)
:
m_port{port_num},
m_ip{},
m_exit{false},
m_l_sock_fd{-1},
m_sock_fd{-1}
{
  // open the m_l_sock_fd socket of type SOCK_STREAM
  m_l_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  // check if the socket creation was successful
  if (m_l_sock_fd < 0){ 
    std::cout << "ERROR: OPEN SOCKET" << std::endl;
    return;
  }
  // call the function to set the options and bind,
  // and close the socket and return if not successful
  if(!optionsAndBind()) {
    std::cout << "ERROR: BIND" << std::endl;
    close(m_l_sock_fd);
    return;
  }
}

TcpWrapper::~TcpWrapper() {
  // call the function quit
  quit();
}


void 
TcpWrapper::quit() {
  // set m_exit to be true
  m_exit = true;

  // if m_l_sock_fd is open, close it and set the 
  // file descriptor to -1
  if(m_l_sock_fd >= 0) {
    close(m_l_sock_fd);
    m_l_sock_fd = -1;
  }

  // if m_sock_fd is open, close it and set the 
  // file descriptor to -1
  if(m_sock_fd >= 0){
    close(m_sock_fd);
    m_sock_fd = -1;
  }
}


void 
TcpWrapper::runServer() {
  // create a char buffer called buf, of size C_MTU
  char buf[C_MTU];

  // wait for a client to connect
  if(acceptClient()) {

    // start a while loop to receive data and send application ACKs to this client
    // the loop ends when m_exit is true
    while(!m_exit) {

      // call recvData, passing buf, to receive data
      // save the return value of recvData in a data_size variable
      int data_size = recvData(buf);

      // check if the data_size is smaller than 0
      // if yes, set m_exit to true and break the loop
      if (data_size < 0) {
        std::cout << "Terminate - socket recv error" << std::endl;
        m_exit = true;
        break;
      } 
      // check if the data_size is equal to 0
      // if yes, set m_exit to true and break the loop
      else if (data_size == 0) {
        std::cout << "Terminate - the other endpoint has closed the socket" << std::endl;
        m_exit = true;
        break;
      } 

      // print the buf to the terminal
      std::cout << buf;

      // reset the buffer for a new read using memset
      memset(buf, 0, C_MTU); // this cleans the buffer for a new read

      // send an application ACK to the other endpoint
      std::string to_tx = "Packet ACK\n";
      if(sendData(to_tx.c_str(), to_tx.length()) >= 0) {
        std::cout << "TX successful" << std::endl;
      } else {
        // if the transmission was not successful, set m_exit to true and break the loop
        m_exit = true;
        break;
      }
    }
  }
}


bool 
TcpWrapper::optionsAndBind() {
  // set the options for the socket
  int option(1);
  setsockopt(m_l_sock_fd, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  struct sockaddr_in my_addr = {0}; // set all elements of the struct to 0
  my_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert m_port to network number format
  my_addr.sin_port = htons(m_port); 
  // accept connection from all interfaces of the Network Interface Card (NIC)
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // bind the socket to the m_port
  if (bind(m_l_sock_fd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { 
    std::cout << "ERROR: BIND SOCKET" << std::endl;
    if(m_l_sock_fd>=0) {
      close(m_l_sock_fd);
    }
    return false;
  }

  // accept at most 1 client at a time, and set the socket in a listening state
  if (listen(m_l_sock_fd, 1) < 0) { 
    std::cout << "ERROR: LISTEN SOCKET" << std::endl;
    
    return false;
  }
  return true;
}


bool 
TcpWrapper::acceptClient() {
  // prepare the struct to store the client address
  struct sockaddr_in client_addr;
  socklen_t addr_l = sizeof(client_addr);

  // call the accept API on the socket
  m_sock_fd = ::accept(m_l_sock_fd, (struct sockaddr*) &client_addr, &addr_l);

  // if the m_sock_fd does not open successfully, close the listening socket, and return false
  if(m_sock_fd < 0) {
    std::cout << "ERROR: ACCEPT CONNECTION" << std::endl;
    if(m_l_sock_fd>=0) {
      close(m_l_sock_fd);
      m_l_sock_fd = - 1;
    }
    return false;
  }

  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " 
            << inet_ntoa(client_addr.sin_addr) << std::endl; 

  // save the client IP in the m_ip string
  m_ip = inet_ntoa(client_addr.sin_addr);
  return true;
}


int 
TcpWrapper::recvData(char* buf)  
{
  if(m_sock_fd<0) {
    return -1;
  }
  // call the recv API
  int rcv_size = ::recv(m_sock_fd, buf, C_MTU, 0);
  // check if the recv size is ok or not
  if(rcv_size < 0) {
    std::cout << "ERROR: RECV" << std::endl;

    // here we close just m_sock_fd because, in principle,
    // the m_l_sock_fd can be used for other clients (not in this case, though)
    if(m_sock_fd >= 0) {
      close(m_sock_fd);
      m_sock_fd = -1;
    }
  }
  return rcv_size;
}


int
TcpWrapper::sendData(const char* buf, size_t size_to_tx) 
{
  if(m_sock_fd<0) {
    return -1;
  }
  int sent_size = ::send(m_sock_fd,buf,size_to_tx,0); // send the data through sckfd
  if(sent_size < 0) { // the send returns a size of -1 in case of errors
    std::cout << "ERROR: SEND" << std::endl;
    if(m_sock_fd >= 0) {
      close(m_sock_fd);
      m_sock_fd = -1;
    } // if error close the socket and exit
    return -4;
  }
  return sent_size;
}

void 
TcpWrapper::print(std::ostream& out) const
{
  out << "TCP socket on port " << m_port;
}
