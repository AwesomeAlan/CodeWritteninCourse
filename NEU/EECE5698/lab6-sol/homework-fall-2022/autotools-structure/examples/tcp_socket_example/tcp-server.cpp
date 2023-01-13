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
#include <cmath>

/**
 * Method to invert the elements of the buffer
 * @param buf the buffer
 * @param size the number of elements in the buffer
 */
void invertBuffer(char* buf, size_t size) 
{
  // suggestions: 
  // - use a for loop that iterates up to half of the size of the string (not considering the last termination char) 
  // - use a temporary char variable
  // - debug by printing your results at each cycle iteration
  // - pay attention to the index
  //   Do not place buffer[size - 1] as first, because this is a 
  //   zero-terminated string..

  size_t net_size {size - 2}; // we do not want to consider the termination character
  for(size_t index = 0; index < std::floor(net_size / 2); ++index)
  {
    char tmp = buf[index]; // save into a temporary char
    buf[index] = buf[net_size - index]; // swap
    buf[net_size - index] = tmp; // swap
  }

}

int main(int argc, char** argv) {

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./tcp_server has argc = 1 and no command line arguments
  //   ./tcp_server 55556 has argc = 2 and the socket port as argument
  const int listen_port = argc ==1 ? 55555 : atoi(argv[1]);

  // open a SOCK_STREAM (TCP) socket
  int scklist = socket(AF_INET, SOCK_STREAM, 0);
  if (scklist < 0){ 
    std::cout << "ERROR: OPEN SOCKET " << scklist << std::endl;
    close(scklist);
    return -1;
  }
  // set socket options to release the socket address immediately after 
  // the socket is closed
  int option(1);
  setsockopt(scklist, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  struct sockaddr_in my_addr = {0}; // set all elements of the struct to 0
  my_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert listener_port to network number format
  my_addr.sin_port = htons(listen_port); 
  // accept connection from all interfaces of the Network Interface Card (NIC)
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // bind the socket to the port
  if (bind(scklist,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { 
    std::cout << "ERROR: BIND SOCKET" << std::endl;
    close(scklist);
    return -2;
  }

  // Accept at max 1 client at a time: by changing 1 to 5 in the next line 
  // you accept at most the connection of 5 clients in parallel.
  if (listen(scklist, 1) < 0) { 
    std::cout << "ERROR: LISTEN SOCKET" << std::endl;
    close(scklist);
    return -3;
  }

  struct sockaddr_in client_addr;
  socklen_t addr_l = sizeof(client_addr);

  // the next line does 3 operations:
  // 1) it accepts the connection of a new client.
  // 2) it creates a new socket used to perform the actual data transmission 
  //    between client ad server. If the socket creation fails, it returns -1.
  // 3) it Saves into client_addr the address of the client connected, so you 
  //    can know who is sending what.
  int sockfd = accept(scklist, (struct sockaddr*) &client_addr, &addr_l);
  if(sockfd < 0) {
    std::cout << "ERROR: ACCEPT CONNECTION" << std::endl;
    close(sockfd);
    close(scklist);
    return -4;
  }

  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << std::endl; 

  // receive from sockfd
  const size_t max_size = 256;
  char buf[max_size] = {0};

  int rcv_size = recv(sockfd, buf, max_size, 0);
  if(rcv_size < 0) {
    std::cout << "ERROR: RECV" << std::endl;
    close(sockfd);
    close(scklist);
    return -5;
  }
  std::cout << "Received: " << buf << std::endl;
  std::cout << "Size: " << rcv_size << std::endl;
  
  /**
   * send back to the client whatever you received, 
   * - first try without modifing (i.e., as it is) 
   * - then (optional) by inverting the buffer order, implementing 
   *   the function void invertBuffer(char* buf,size_t size)
   */

  // call invert buffer
  invertBuffer(buf,rcv_size);
 
  // call the send API and check if the sent size if larger than 0
  int sent_size = send(sockfd, buf, rcv_size, 0);
  if(sent_size < 0)
  {
    std::cout << "ERROR: SEND" << std::endl;
    close(sockfd);
    close(scklist);
    return -6;
  }

  // close the sockets
  close(sockfd);
  close(scklist);
}
