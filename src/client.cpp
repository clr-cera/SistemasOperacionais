#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>

#include "./lib/lib.h"

class Client {
public:
    int clientSocket;

    explicit Client(const int port) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        if(connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress))) {
            std::cerr << "Failed to connect to server" << std::endl;
            exit(1);
        }

        std::cout << "Connected to Server!" << std::endl;
    }
};

int main() {
    const Client client = Client(PORT);
}