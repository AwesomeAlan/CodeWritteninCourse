/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

/**
 * Method to replace the buffer with capital letters
 * @param buf the buffer
 * @param size the number of elements in the buffer
 */
void toUpper(char* buf, size_t size) {
  for (size_t index = 0; index < size; ++index) {
    buf[index] = toupper(buf[index]);
  }
}

int main(int argc, char** argv) {


  // READ from argv the command line argument vector, by checking the arguments 
  // counter (argc), i.e.,
  //   ./udp_server has argc = 1 and no command line arguments
  //   ./udp_server 55556 has argc = 2 and the socket port as argument
  const int recv_port = argc ==1 ? 55555 : atoi(argv[1]);

  // open a SOCK_DGRAM (UDP) socket
  int sckfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sckfd < 0){ 
    std::cout << "sckfd < 0" ; return -1;
  }
 int option(1);
 setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, 
            (char*)&option, sizeof(option));
  struct sockaddr_in my_addr = {0};
  struct sockaddr_in srcaddr; 
  socklen_t addrlen = sizeof(srcaddr);
  my_addr.sin_family = AF_INET;

  my_addr.sin_port = htons(recv_port);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);  

  if (bind(sckfd, (struct sockaddr*) &my_addr, sizeof(my_addr))<0) {
    close(sckfd); 
    std::cout << "bind socket address failed";
    return -2;
  }
  const size_t max_size = 256;
  char buffer[max_size] = {0}; 
  

  // UDP is not connected: we just receive from someone (that may change time 
  // by time) and that's it. We can check how sent something storing its 
  // addess to srcaddr and send him back something through the same socket.
  int size = recvfrom(sckfd, buffer, max_size, 0, (struct sockaddr *)   
                      &srcaddr, &addrlen);
  char* ip = inet_ntoa(srcaddr.sin_addr);
  std::cout << ip << std::endl;
  std::cout << buffer << std::endl; 
  
  toUpper(buffer,size);
  
  int sent_size = sendto(sckfd, buffer, size, 0, (struct sockaddr *) &srcaddr, addrlen);
  if (sent_size < 0) {
    close(sckfd);
    return -3;
  }

  close(sckfd);
}

