#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <vector>
#include <stdlib.h>

class Server {
  std::vector<int> connections;
  int serverSocket;

  void set_socket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(6969);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress))) {
      exit(1);
    }

    listen(serverSocket, 5);
  }

  void accept_connection() {
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    connections.push_back(clientSocket);
  }

};

