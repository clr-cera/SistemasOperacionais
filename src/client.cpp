#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <thread>

#include "./lib/lib.h"

class Client {
public:
    int clientSocket;

    explicit Client(const int port) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0); // Makes it TCP

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET; // TCP
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.s_addr = IP;

        if(connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress))) {
            std::cerr << "Failed to connect to server" << std::endl;
            exit(1);
        }

        std::cout << "Connected to Server!" << std::endl;
    }

    // Thread que lê do usuário e envia mensagens
    [[noreturn]] void send_loop() {
        while(true) {
            char buffer[BUFFER_SIZE];
            std::cin >> buffer;
            send(clientSocket, buffer, strlen(buffer), 0);
            clean_buffer(buffer);
        }
    }

    // Thread que lê mensagens e printa
    [[noreturn]] void receive_loop() {
        while(true) {
            char buffer[BUFFER_SIZE];
            recv(clientSocket, buffer, BUFFER_SIZE, 0);
            std::cout << buffer << std::endl;
        }
    }
};

int main() {
    Client client = Client(PORT);

    std::thread sendThread(&Client::send_loop, &client);
    std::thread receiveThread(&Client::receive_loop, &client);

    sendThread.join();
    receiveThread.join();
}