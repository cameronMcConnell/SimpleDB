#include "lib/headers/input-handler.hpp"
#include "lib/headers/command-parser.hpp"
#include "lib/headers/errors.hpp"

#include <string.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

int parseArgs(int argc, char* argv[], int &portNumber, bool &socketFlag) {
    if (argc > 3) {
        std::cerr << "SYNTAX ERROR; TOO MANY ARGUEMENTS; SCHEMA IS SimpleDB -p <port_number> || SimpleDB;\n";
        return 1;
    }

    if (argc == 1) {
        socketFlag = false;
    }
    else if (argc == 3) {
        if (strcmp(argv[1], "-p") != 0) {
            std::cerr << "SYNTAX ERROR; SCHEMA IS SimpleDB -p <port_number> || SimpleDB;\n";
            return 1;
        }

        portNumber = std::stoi(argv[2]);
        socketFlag = true;
    }
    else {
        std::cerr << "SYNTAX ERROR; SCHEMA IS SimpleDB -p <port_number> || SimpleDB;\n";
        return 1;
    }

    return 0;
}

int directoryExists() {
    const char* dir = "./tables";
    struct stat sb;
    return stat(dir, &sb);
}

int main(int argc, char *argv[]) {
    int portNumber;
    bool socketFlag;

    if (parseArgs(argc, argv, portNumber, socketFlag) == 1) {
        return 1;
    }

    if (directoryExists() != 0 && mkdir("tables", 0777) == -1) {
        return 1;
    }

    std::cout << "+-------------------------+\n";
    std::cout << "| SimpleDB | VERSION: 1.0 |\n";
    std::cout << "+-------------------------+" << std::endl;

    CommandParser commandParser = CommandParser();

    if (socketFlag) {
        SocketInputHandler inputHandler = SocketInputHandler(portNumber);

        try {
            inputHandler.openSocket();
        }
        catch (const SocketError& e) {
            std::cerr << e.what() << '\n';
            return 1;
        }

        while (1) {
            std::string command = inputHandler.getInput();
            if (command.empty()) {
                continue;
            }

            if (command == "QUIT"){
                std::cout << "QUITTING PROGRAM;\n";
                inputHandler.closeSocket();
                return 0;
            }

            commandParser.parseCommand(command);
        }
    }
    else {
        UserInputHandler inputHandler;
        
        while (1) {
            std::cout << commandParser.getActiveTable() + "-> ";
            std::string command = inputHandler.getInput();

            if (command == "QUIT") {
                std::cout << "QUITTING PROGRAM;\n";
                return 0;
            }

            commandParser.parseCommand(command);
        }
    }
}