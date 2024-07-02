#include "headers/command-parser.hpp"

CommandParser::CommandParser() {
    executionHandler = ExecutionHandler();
}

std::string CommandParser::trim(std::string command) {
    size_t i = 0, j = command.length() - 1;

    while (i < command.length() && command[i] == ' ') {
        i += 1;
    }

    if (i == command.length()) {
        return "";
    }

    while (j > i && command[j] == ' ') {
        j -= 1;
    }

    return command.substr(i, j + 1);
}

void CommandParser::parseCommand(std::string command) {
    command = trim(command);
    size_t index = command.find(' ');
    std::string token = command.substr(0, index);

    if (token == "CREATE") {
        try {
            if (index > command.length()) {
                throw "SYNTAX ERROR; NO TABLE NAME";
            }

            // Get table name
            command = trim(command.substr(index + 1, command.length()));
            index = command.find(' ');
            std::string tableName = command.substr(0, index);

            if (tableName.empty()) {
                throw "SYNTAX ERROR; NO TABLE NAME";
            }
            else if (index > command.length()) {
                throw "SYNTAX ERROR; WITH IS NOT INCLUDED";
            }

            // Remove With from the command
            command = trim(command.substr(index + 1, command.length()));
            index = command.find(' ');
            std::string with = command.substr(0, index);

            if (with != "WITH") {
                throw "SYNTAX ERROR; WITH IS NOT INCLUDED";
            }
            else if (index > command.length()) {
                throw "SYNTAX ERROR; NO SUPLLIED HEADERS";
            }

            // Get the headers
            command = trim(command.substr(index + 1, command.length()));
            std::vector<std::string> headers;
            std::stringstream ss(command);

            while (ss.good()) {
                std::string header;
                getline(ss, header, ',');
                if (header.find(' ') < header.length()) {
                    throw "SYNTAX ERROR; HEADER MUST NOT CONTAIN WHITESPACE";    
                }
                headers.push_back(header);
            }

            if (headers.size() == 0) {
                throw "SYNTAX ERROR; NO SUPPLIED HEADERS";
            }

            // Create table with headers
            executionHandler.create(tableName, headers);

            std::cout << "SUCCESS WITH CREATING TABLE: " << tableName << std::endl;
        }
        catch (const char *message) {
            std::cout << message << std::endl;
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
        //CommandParser::parseSelect(command.substr(index + 1, command.length()));
    }
    else if (token == "INSERT") {
        //CommandParser::parseInsert(command.substr(index + 1, command.length()));
    }
    else if (token == "DELETE") {
        //CommandParser::parseDelete(command.substr(index + 1, command.length()));
    }
    else if (token == "UPDATE") {
        //CommandParser::parseUpdate(command.substr(index + 1, command.length()));
    }
    else {
        std::cout << "SYNTAX ERROR; INVALID TOKEN: " << token << '\n'; 
    }
}

void CommandParser::parseSelect(std::string command) {

}

void CommandParser::parseInsert(std::string command) {
    
}

void CommandParser::parseDelete(std::string command) {
    
}

void CommandParser::parseUpdate(std::string command) {
    
}