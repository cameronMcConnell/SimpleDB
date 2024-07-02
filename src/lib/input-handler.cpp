#include "headers/input-handler.hpp"

std::string UserInputHandler::getInput() {
    std::string input;
    std::cin >> input;
    return input;
}

SocketInputHandler::SocketInputHandler(int portNumber) {
    this->portNumber = portNumber;
}

std::string SocketInputHandler::getInput() {
    char buffer[200];
    
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1) {
        std::cerr << "ERROR RECEIVING DATA FROM CLIENT\n";
        return "";
    }
    
    buffer[bytesReceived] = '\0';

    return std::string(buffer);
}

void SocketInputHandler::openSocket() {
    // Create socket
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1){
        throw "ERROR CREATING SOCKET";
    }

    // Create address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "ERROR BINDING SOCKET";
    }

    // Listen on the socket
    if (listen(this->serverSocket, 5) == -1) {
        throw "ERROR LISTENING ON SOCKET";
    }

    // Accept only one client connection
    this->clientSocket = accept(this->serverSocket, nullptr, nullptr);
    if (this->clientSocket == -1) {
        throw "ERROR ACCEPTING CLIENT CONNECTION";
    }
}

void SocketInputHandler::closeSocket() {
    close(this->serverSocket);
}