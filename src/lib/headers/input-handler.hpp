#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 

class InputHandler {
    public:
        virtual std::string getInput() = 0;
};

class UserInputHandler : public InputHandler {
    public:
        std::string getInput();
};

class SocketInputHandler : public InputHandler{
    private:
        int serverSocket;
        int clientSocket;

    public:
        SocketInputHandler(int portNumber);
        std::string getInput();
        void closeSocket();
};

#endif