/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-client-fwd.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

TcpClientForwarder::TcpClientForwarder(const std::string& ip_addr, int port_num)
:
EthConn(ip_addr,port_num),
forward_to()
{
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0){ 
    std::cout << "ERROR: OPEN SOCKET" << std::endl;
    close(sock_fd);
    return;
  }
  if(!connectToServer()) {
  	std::cout << "ERROR: CONNECT" << std::endl;
    close(sock_fd);
    return;
  }
}

TcpClientForwarder::~TcpClientForwarder() {
  if(sock_fd >= 0) {
    close(sock_fd);
  }
  std::cout << "TcpClientForwarder destructor" << std::endl;
}

bool TcpClientForwarder::connectToServer() 
{
  int option(1);
  if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option)) < 0) {
    std::cout << "ERROR SET SOCKET OPTIONS" << std::endl;
    close(sock_fd); // if conversion fail, close the socket and return error -2
    return false;
  }
  struct sockaddr_in dest_addr = {0}; // set all elements of the struct to 0
  dest_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert port to network number format
  dest_addr.sin_port = htons(port); 
  // convert dest_ip from char* to network address
  if (inet_pton(AF_INET, ip.c_str(), &dest_addr.sin_addr) <= 0) { 
    std::cout << "ERROR CONVERTING IP TO INTERNET ADDR" << std::endl;
    close(sock_fd); // if conversion fail, close the socket and return error -2
    return false;
  }

  //CONNECT THE SOCKET TO THE SERVER IP:PORT SPECIFIED INTO DEST_ADDR
  if (connect(sock_fd, (struct sockaddr*) &dest_addr, sizeof(dest_addr)) < 0) { 
    std::cout << "ERROR: CONNECT" << std::endl;
    close(sock_fd); // if connection failed return
    return false;
  }
  return true;
}

bool TcpClientForwarder::forwardCycle(size_t num_times) {
  if(forward_to.expired()) {
    std::cout << "ERROR: forward_to pointer not valid" << std::endl;
    return false;
  }
  // For num_times times it receives data from the connected server, and
  // forwards it to the forward_to connection
  for(size_t n_cycle = 0; n_cycle < num_times; n_cycle++) {
    auto buffer = std::make_shared<std::array<char,MTU>>();
    int rx_bytes = receive(buffer);
    if(rx_bytes < 0) {
      std::cout << "ERROR: rx_bytes < 0" << std::endl;
      return false;
    }
    std::cout << "rx data = " << buffer->data() 
              << ", size = " << rx_bytes << std::endl;
    if(!forward_to.expired()) {
      int sent_bytes = forward_to.lock()->transmit(buffer,rx_bytes);
      if(rx_bytes != sent_bytes) {
        std::cout << "ERROR: rx_bytes is not equal to sent_bytes" << std::endl;
        return false;
      }
      std::cout << "data forwarded" << std::endl;
    }
  }
  std::cout << "END OF FORWARDING CICLE FOR THIS CLIENT" << std::endl;
  return true;
}

int TcpClientForwarder::receive(std::shared_ptr<std::array<char,MTU>> buf)  
{
  if(sock_fd < 0) {
    return -1;
  }
  int rcv_size = recv(sock_fd,buf->data(),buf->max_size(),0);
  if(rcv_size < 0) {
    std::cout << "ERROR: RECV" << std::endl;
    close(sock_fd);
    sock_fd = -1;
  }
  return rcv_size;
}


int TcpClientForwarder::transmit(std::shared_ptr<std::array<char,MTU>> buf, 
  size_t size_to_tx) 
{
  if(sock_fd < 0) {
    return -1;
  }
  int sent_size = send(sock_fd,buf->data(),size_to_tx,0); // send the data through sock_fd
  if(sent_size < 0) { // the send returns a size of -1 in case of errors
    std::cout << "ERROR: SEND" << std::endl;
    close(sock_fd); // if error close the socket and exit
    sock_fd = -1;
  }
  return sent_size;
}

// Exercise 2b: implement setForwarder
void 
TcpClientForwarder::setForwarder(std::shared_ptr<EthConn> forwarder)
{
  forward_to = forwarder;
}


void 
TcpClientForwarder::print (std::ostream& out)
{
  out << "TcpClientForwarder socket " << sock_fd;
}