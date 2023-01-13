/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese 
*/

#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) 
{
  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //    ./tcp_client has argc = 1 and no command line arguments
  //    ./tcp_client 192.168.100.12 has argc = 2 and the IP address as argument
  //    ./tcp_client 192.168.100.12 55556 has argc = 3 and IP and socket port as 
  //      arguments
  const char* dest_ip = argc == 1 ? "127.0.0.1" : argv[1];
  const int dest_port = argc > 2 ? atoi(argv[2]) : 55555;

  // open a SOCK_STREAM (TCP) socket
  int sckfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sckfd < 0){ 
    std::cout << "ERROR: OPEN SOCKET" << std::endl;
    close(sckfd);
    return -1;
  }

  // set socket options to release the socket address immediately after 
  // the socket is closed
  int option(1);
  setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));

  // set server destination address 
  struct sockaddr_in dest_addr = {0}; // set all elements of the struct to 0
  dest_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert dest_port to network number format
  dest_addr.sin_port = htons(dest_port); 
  // convert dest_ip from char* to network address
  if (inet_pton(AF_INET, dest_ip, &dest_addr.sin_addr) <= 0) { 
    std::cout << "ERROR CONVERTING IP TO INTERNET ADDR" << std::endl;
    close(sckfd); // if conversion fail, close the socket and return error -2
    return -2;
  }

  // connect the socket to the server ip:port specified into dest_addr
  if (connect(sckfd, (struct sockaddr*) &dest_addr, sizeof(dest_addr)) < 0) { 
    std::cout << "ERROR: CONNECT" << std::endl;
    close(sckfd); // if connection failed return
    return -3;
  }

  // transmit data
  const size_t max_size = 512;
  char buf[max_size] = "Payload"; // store the data in a buffer
  std::cout << "Transmit " << buf << std::endl;
  size_t data_size = 8; // transmit the termination character too!
  int sent_size = send(sckfd,buf,data_size,0); // send the data through sckfd
  if(sent_size < 0) { // the send returns a size of -1 in case of errors
    std::cout << "ERROR: SEND" << std::endl;
    close(sckfd); // if error close the socket and exit
    return -4;
  }

  // set buffer to zero for next read
  memset(buf, 0, max_size);

  // wait to receive data
  int rcv_size = recv(sckfd,buf,max_size,0);
  if(rcv_size < 0) {
    std::cout << "ERROR: RECV" << std::endl;
    close(sckfd);
    //close(scklist);
    return -5;
  }
  std::cout << buf << std::endl;
  
  // close the socket
  close(sckfd);
}

