/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-client-fwd.h>
#include <iostream>
#include <thread>

int main(int argc, char** argv) 
{
  // declare some variables
  const char* server_ip1 = "127.0.0.1";
  const char* server_ip2 = "127.0.0.1";
  const int server_port1 = 55556;
  const int server_port2 = 55557;

  // Exercise 3: create and assign to a shared_ptr an object of type TcpClientForwarder,
  // by passing to its constructor (through make_shared) server_ip1 and server_port1
  std::shared_ptr<TcpClientForwarder> client1 {std::make_shared<TcpClientForwarder>(server_ip1, server_port1)};

  // Exercise 4: create and assign to a shared_ptr an object of type TcpClientForwarder,
  // but, in this case, the shared_ptr should be of type EthConn (which is the base
  // class for TcpClientForwarder).
  // Pass to its constructor (through make_shared) server_ip2 and server_port2
  std::shared_ptr<EthConn> client2 {std::make_shared<TcpClientForwarder>(server_ip2, server_port2)};

  // Exercise 5: call setForwarder on client1, passing client2
  client1->setForwarder(client2);

  // Exercise 6: uncomment the following lines (threads are still new for us - we'll see them next week)
  auto forwarder_thr1 = std::thread(
    &TcpClientForwarder::forwardCycle, client1, 10);

  // Exercise 7
  std::shared_ptr<TcpClientForwarder> casted_client {std::dynamic_pointer_cast<TcpClientForwarder>(client2)};  
  
  if (casted_client == nullptr) {
    std::cout << "Cast not successful" << std::endl;

    if(forwarder_thr1.joinable()) {
      forwarder_thr1.join();
      std::cout << "thr1 joint" << std::endl;
    }

    return 0;
  }

  casted_client->setForwarder(client1);


  // Exercise 8: uncomment the following lines (threads are still new for us - we'll see them next week)
  auto forwarder_thr2 = std::thread(
    &TcpClientForwarder::forwardCycle, casted_client, 10);
  
  if(forwarder_thr1.joinable()) {
    forwarder_thr1.join();
    std::cout << "thr1 joint" << std::endl;
  }
  if(forwarder_thr2.joinable()) {
    forwarder_thr2.join();
    std::cout << "thr2 joint" << std::endl;
  }

  return 0;

}