#include "headers/command-parser.hpp"

CommandParser::CommandParser(std::string activeTable) {
    executionHandler = ExecutionHandler();
    this->activeTable = activeTable;
}

std::vector<std::string> CommandParser::tokenize(std::string command) {
    std::vector<std::string> tokens;
    std::string token;
    const char delimeter = ' ';
    std::istringstream iss(command);

    while (std::getline(iss, token, delimeter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void CommandParser::checkForValidSize(std::vector<std::string> tokens, size_t size) {
    if (tokens.size() != size) {
        throw "SYNTAX ERROR; INVALID COMMAND;";
    }
}

void CommandParser::parseCommand(std::string command) {
    std::vector<std::string> tokens = tokenize(command);

    if (tokens.empty()) {
        std::cout << "SYNTAX ERROR; NO COMMAND SUPPLIED;" << std::endl;
    }
    else if (tokens[0] == "CREATE") {
        try {
            checkForValidSize(tokens, 4);
            parseCreate(tokens);
        }
        catch (const char *message) {
            std::cout << message << std::endl;
        }
    }
    else if (tokens[0] == "DROP") {
        try {
            checkForValidSize(tokens, 2);
            parseDrop(tokens);
        }
        catch (const char *message) {
            std::cout << message << std::endl;
        }
    }
    else if (tokens[0] == "USE") {
        try {
            checkForValidSize(tokens, 2);
            parseUse(tokens);
        }
        catch (const char *message) {
            std::cout << message << std::endl;
        }
    }
    else if (tokens[0] == "SELECT") {
    
    }
    else if (tokens[0] == "INSERT") {
    
    }
    else if (tokens[0] == "DELETE") {
    
    }
    else if (tokens[0] == "UPDATE") {
    
    }
    else {
        std::cout << "SYNTAX ERROR; INVALID TOKEN: " << tokens[0] << ";" << std::endl; 
    }
}

void CommandParser::parseCreate(std::vector<std::string> tokens) {
    std::string tableName = tokens[1];

    if (tokens[2] != "WITH") {
        throw "SYNTAX ERROR; WITH NOT INCLUDED;";
    }

    std::vector<std::string> headers;
    std::string header;
    const char delimeter = ',';
    std::istringstream iss(tokens[3]);

    while (std::getline(iss, header, delimeter)) {
        if (header == ""){
            throw "SYNTAX ERROR; HEADERS MUST NOT CONTAIN EMPTY STRINGS;";
        }

        headers.push_back(header);
    }

    executionHandler.create(tableName, headers);

    std::cout << "SUCCESS IN CREATING TABLE: " << tableName << ";" << std::endl;
}

void CommandParser::parseDrop(std::vector<std::string> tokens) {
    std::string tableName = tokens[1];

    executionHandler.drop(tableName);

    std::cout << "SUCCESS IN DROPPING TABLE: " << tableName << ";" << std::endl;
}

void CommandParser::parseUse(std::vector<std::string> tokens) {
    std::string tableName = tokens[1];

    executionHandler.use(tableName);

    this->activeTable = tableName;

    std::cout << "SUCCESS IN USING TABLE: " << tableName << ";" << std::endl;
}

void CommandParser::parseSelect(std::vector<std::string> tokens) {

}

void CommandParser::parseInsert(std::vector<std::string> tokens) {
    
}

void CommandParser::parseDelete(std::vector<std::string> tokens) {
    
}

void CommandParser::parseUpdate(std::vector<std::string> tokens) {
    
}