#include "headers/input-handler.hpp"

std::string UserInputHandler::getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

SocketInputHandler::SocketInputHandler(int portNumber) {
    this->portNumber = portNumber;
}

std::string SocketInputHandler::getInput() {
    char buffer[400];
    
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1) {
        throw SocketError("ERROR RECEIVING DATA FROM CLIENT");
        return "";
    }
    
    buffer[bytesReceived] = '\0';

    std::cout << "MESSAGE RECEIVED FROM CLIENT: " << buffer << std::endl;

    return std::string(buffer);
}

void SocketInputHandler::openSocket() {
    // Create socket
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1){
        throw SocketError("ERROR CREATING SOCKET");
    }

    // Create address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw SocketError("ERROR BINDING SOCKET");
    }

    // Listen on the socket
    if (listen(this->serverSocket, 5) == -1) {
        throw SocketError("ERROR LISTENING ON SOCKET");
    }

    std::cout << "SOCKET OPEN ON PORT: " << portNumber << "; AWAITING CONNECTION FROM CLIENT;" << std::endl;

    // Accept only one client connection
    this->clientSocket = accept(this->serverSocket, nullptr, nullptr);
    if (this->clientSocket == -1) {
        throw SocketError("ERROR ACCEPTING CLIENT CONNECTION");
    }

    std::cout << "SOCKET ACCEPTING MESSAGES ON PORT: " << portNumber << std::endl;
}

void SocketInputHandler::sendOutput(std::string output) {
    send(this->clientSocket, output.c_str(), output.size(), 0);
}

void SocketInputHandler::closeSocket() {
    close(this->serverSocket);
}