#include "lib/headers/input-handler.hpp"
#include "lib/headers/command-parser.hpp"
#include <string.h>

int main(int argc, char *argv[]) {
    int portNumber;
    bool socketFlag;

    if (parseArgs(argc, argv, portNumber, socketFlag) == 1) {
        return 1;
    }

    CommandParser commandParser = CommandParser();

    if (socketFlag) {
        SocketInputHandler inputHandler = SocketInputHandler(portNumber);

        while (1) {
            std::string command = inputHandler.getInput();

            if (command == "QUIT"){
                std::cout << "QUITTING PROGRAM\n";
                inputHandler.closeSocket();
                return 0;
            }

            commandParser.parseCommand(command);
        }
    }
    else {
        UserInputHandler inputHandler;
        
        while (1) {
            std::string command = inputHandler.getInput();

            if (command == "QUIT") {
                std::cout << "QUITTING PROGRAM\n";
                return 0;
            }

            commandParser.parseCommand(command);
        }
    }
}

int parseArgs(int argc, char* argv[], int &portNumber, bool &socketFlag) {
    if (argc > 3) {
        std::cerr << "SYNTAX ERROR; TOO MANY ARGUEMENTS; SCHEMA IS SimpleDB -p <port_number> || SimpleDB\n";
        return 1;
    }

    if (argc == 1) {
        socketFlag = false;
    }
    else if (argc == 3) {
        if (strcmp(argv[1], "-p") != 0) {
            std::cerr << "SYNTAX ERROR; SCHEMA IS SimpleDB -p <port_number> || SimpleDB\n";
            return 1;
        }

        portNumber = std::stoi(argv[2]);
        socketFlag = true;
    }
    else {
        std::cerr << "SYNTAX ERROR; SCHEMA IS SimpleDB -p <port_number> || SimpleDB\n";
        return 1;
    }

    return 0;
}