/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <service.h>
#include <string.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>

const unsigned int Service::FILE_SIZE = 4;

Service::Service(int sk_fd)
:
sock_fd(sk_fd),
total_received_size(0)
{
  std::cout << "constructor, sock_fd = " << sock_fd << std::endl;
  servent_daemon = std::thread(&Service::run, this);
}

Service::~Service()
{
  if (sock_fd > -1) {
  	close(sock_fd);
  }

  if(servent_daemon.joinable()) {
  	servent_daemon.join();
  }
}


void Service::run() 
{

  const size_t MAX_BUF_SIZE = 100;
  char buffer[MAX_BUF_SIZE] = {0};

  std::cout << "Service::run" << std::endl;
  while(sock_fd > -1 && total_received_size < Service::FILE_SIZE) {
    size_t to_read {std::min(MAX_BUF_SIZE, (size_t)Service::FILE_SIZE - total_received_size)};
    std::cout << "to_read " << to_read << "\n"; 
    ssize_t recv_data {::recv(sock_fd, buffer, to_read, 0)};

    if (recv_data < 0) {
    	std::cout << "Error in read " << recv_data << "\n";
    	close(sock_fd);
    	return;
    } else if (recv_data == 0) {
    	std::cout << "The other endpoint has closed the socket\n";
    	close(sock_fd);
    	return;
    }
    
    total_received_size += recv_data;

    std::string message = getReport();

    ssize_t sent_data {::send(sock_fd, message.c_str(), message.size(), 0)};
	if (sent_data < 0) {
    	std::cout << "Error in send " << sent_data << "\n";
    	close(sock_fd);
    	return;
    }

    memset(buffer,0,MAX_BUF_SIZE);
  }

  if(sock_fd > -1) {
    std::cout << "Service finished in socket " << sock_fd << std::endl;
    close(sock_fd);
    sock_fd = -1;
    return;
  }
}

std::string
Service::getReport() const
{
	return "Number of bytes received = " + std::to_string(total_received_size) + 
		 ", over a total of " + std::to_string(Service::FILE_SIZE) + " bytes \n";
}

int
Service::getSockFd() const
{
	return sock_fd;
}