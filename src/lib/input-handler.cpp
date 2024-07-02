#include "headers/input-handler.hpp"

std::string UserInputHandler::getInput() {
    std::string input;
    std::cin >> input;
    return input;
}

SocketInputHandler::SocketInputHandler(int portNumber) {
    // Create socket
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Create address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Listen on the socket
    listen(this->serverSocket, 5);

    // Accept only one client connection
    this->clientSocket = accept(this->serverSocket, nullptr, nullptr);
}

std::string SocketInputHandler::getInput() {
    char buffer[200];
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesReceived] = '\0';

    return std::string(buffer);
}

void SocketInputHandler::closeSocket() {
    close(this->serverSocket);
}