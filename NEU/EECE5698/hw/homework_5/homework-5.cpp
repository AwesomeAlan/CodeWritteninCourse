/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <iostream>
#include <chrono>
#include <tcp-wrapper.h>
#include <udp-wrapper.h>
#include <signal.h>
#include <string.h>
#include <vector>
#include <thread>

int
main(int argc, char const *argv[])
{

  struct sigaction act;// structure that contains the handler
  memset(&act, '\0', sizeof(act));
  act.sa_handler = SIG_IGN; // handler that ignores the signal
  if (sigaction(SIGPIPE, &act, NULL) < 0) { // set the handler to
  // SIGPIPE
    std::cerr << "SIGPIPE" << std::endl; //
  }

  // Exercise 2: create a UdpWrapper object in a 
  // std::shared_ptr<SocketWrapper>, pass port 55555 to the 
  // UdpWrapper constructor
  // If by any chance your OS does not support a UDP and a TCP
  // socket on the same port, feel free to change the port number
  std::shared_ptr<SocketWrapper> udp_server = 
      std::make_shared<UdpWrapper>(55555);

  std::shared_ptr<SocketWrapper> tcp_server = 
      std::make_shared<TcpWrapper>(55555);

  // Exercise 3: add the shared_ptr to the UdpWrapper in server_vec
  std::vector<std::shared_ptr<SocketWrapper>> server_vec {tcp_server};
  
  server_vec.push_back(udp_server);

  // Exercise 4: create a vector of std::thread objects
  std::vector<std::thread> thread_vec;

  for (auto serv : server_vec) {
    // Exercise 5: launch a thread that calls the method runServer
    // on serv, and use the push_back function to add the std::thread
    // object to thread_vec
    thread_vec.push_back(std::thread(&SocketWrapper::runServer, serv));
  }

  // pause this thread for 300 s
  std::this_thread::sleep_for(std::chrono::seconds(300));

  // Exercise 6: loop over thread_vec, check if the entries are joinable, 
  // and, if so, join the thread. Feel free to change the duration of the 
  // sleep above to test if this loop executes properly.
  for (auto& th : thread_vec)
  {
    if (th.joinable())
    {
      th.join();
    }
  }

  return 0;
}
