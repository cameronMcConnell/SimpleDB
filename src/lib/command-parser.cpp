#include "headers/command-parser.hpp"

CommandParser::CommandParser() {
    executionHandler = ExecutionHandler();
}

void CommandParser::parseCommand(std::string command) {
    size_t index = command.find(' ');
    std::string token = command.substr(0, index);

    if (token == "CREATE") {
        try {
            std::string tableName = command.substr(index + 1, command.length());
            executionHandler.create(tableName);
            std::cout << "SUCCESS WITH CREATING TABLE: " << tableName << '\n';
        }
        catch (const char *message) {
            std::cout << message;
        }
    }
    else if (token == "DROP") {
        try {
            std::string tableName = command.substr(index + 1, command.length()); 
            executionHandler.drop(tableName);
            std::cout << "SUCCESS WITH DROPPING TABLE: " << tableName << '\n';
        }
        catch (const char *message) {
            std::cout << message;
        }
    }
    else if (token == "SELECT") {
        CommandParser::parseSelect(command.substr(index + 1, command.length()));
    }
    else if (token == "INSERT") {
        CommandParser::parseInsert(command.substr(index + 1, command.length()));
    }
    else if (token == "DELETE") {
        CommandParser::parseDelete(command.substr(index + 1, command.length()));
    }
    else if (token == "UPDATE") {
        CommandParser::parseUpdate(command.substr(index + 1, command.length()));
    }
    else {
        std::cout << "SYNTAX ERROR; INVALID TOKEN: " << token << '\n'; 
    }
}