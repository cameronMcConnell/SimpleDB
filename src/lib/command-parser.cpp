#include "headers/command-parser.hpp"

CommandParser::CommandParser() {
    executionHandler = ExecutionHandler();
}

void CommandParser::parseCommand(std::string command) {
    size_t index = command.find(' ');
    std::string token = command.substr(0, index);

    if (token == "CREATE") {
        try {
            // Get table name
            command = command.substr(index + 1, command.length());
            index = command.find(' ');
            std::string tableName = command.substr(0, index);

            if (tableName.empty()) {
                throw "SYNTAX ERROR; NO TABLE NAME\n";
            }

            // Remove With from the command
            command = command.substr(index + 1, command.length());
            index = command.find(' ');
            std::string with = command.substr(0, index);

            if (with != "WITH") {
                throw "SYNTAX ERROR; WITH IS NOT INCLUDED\n";
            }

            // Get the headers
            command = command.substr(index + 1, command.length());
            std::vector<std::string> headers;
            std::stringstream ss(command);

            while (ss.good()) {
                std::string header;
                getline(ss, header, ',');
                headers.push_back(header);
            }

            if (headers.size() == 0) {
                throw "SYNTAX ERROR; NO SUPLLIED HEADERS\n";
            }

            // Create table with headers
            executionHandler.create(tableName, headers);

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