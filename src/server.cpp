#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "lib/lib.h"

class Server {
public:
  std::vector<int> connections;
  int serverSocket;

  explicit Server(const int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress))) {
      std::cerr << "Failed to bind to port " << port << std::endl;
      exit(1);
    }

    listen(serverSocket, 5);

    std::cout << "Server Started." << std::endl;
  }

  void accept_connection() {
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    connections.push_back(clientSocket);

    std::cout << "New connection." << std::endl;
    std::cout << "Connection number: " << connections.size() << std::endl;
  }


  [[noreturn]] void accept_loop() {
    while(true) {
      accept_connection();
    }
  }

};

int main(){
  Server server = Server(PORT);
  server.accept_loop();
}