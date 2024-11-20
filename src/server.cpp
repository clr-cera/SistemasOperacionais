#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include "lib/lib.h"

class Server {
public:

  // O vetor connections é uma zona crítica,
  // pois são escritas novas conexões e lidas novas mensagem ao mesmo tempo
  std::vector<int> connections;
  std::mutex mutex_connections;

  int serverSocket;

  explicit Server(const int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM makes it TCP

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; // IPV4
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = IP;

    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress))) {
      std::cerr << "Failed to bind to port " << port << std::endl;
      exit(1);
    }

    listen(serverSocket, 5);

    std::cout << "Server Started." << std::endl;
  }

  void accept_connection() {
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    mutex_connections.lock();
    connections.push_back(clientSocket);
    mutex_connections.unlock();

    std::cout << "New connection." << std::endl;
    std::cout << "Connection number: " << connections.size() << std::endl;
  }


  // Thread que aceita novas conexões e escreve em connections
  [[noreturn]] void accept_loop() {
    while(true) {
      accept_connection();
    }
  }

  // Thread que lê mensagens e as reenvia
  [[noreturn]] void receive_loop() {
    while(true) {
      mutex_connections.lock();
      for(auto c : connections) {
        char buffer[1024];
        if (recv(c, buffer, 1024, 0) != 0) {
          std::cout << buffer << std::endl;
          for(auto co : connections) {
            if(c != co) {
              send(co, buffer, 1024, 0);
            }
          }
        }

      }
      mutex_connections.unlock();
    }
  }

};

int main(){
  Server server = Server(PORT);

  std::thread accepterThread(&Server::accept_loop, &server);
  std::thread receiverThread(&Server::receive_loop, &server);

  accepterThread.join();
  receiverThread.join();

  return 0;
}