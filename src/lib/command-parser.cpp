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
        try {
            if (this->activeTable == "root") {
                throw "NOT ACTIVE TABLE IS IN USE.";
            }
            checkForValidSize(tokens, 2);
            parseInsert(tokens);
        }
        catch (const char *message) {
            std::cout << message << std::endl;
        }
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

    if (tableName == this->activeTable) {
        this->activeTable = "root";
    }

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
    std::unordered_map<std::string, std::string> columnValues;
    
    std::string token;
    const char delimeter = ',';
    std::istringstream iss(tokens[1]);

    while (std::getline(iss, token, delimeter)) {
        if (token == "") {
            throw "SYNTAX ERROR; COLUMN VALUES MUST NOT CONTAIN EMPTY STRINGS;";
        }

        size_t index = token.find('=');
        if (index == std::string::npos) {
            throw "SYNTAX ERROR; COLUMN VALUES MUST INCLUDE =;";
        }

        std::string columnName = token.substr(0, index);
        if (columnName == "") {
            throw "SYNTAX ERROR; COLUMN NAMES MUST NOT BE EMPTY STRINGS;";
        }

        std::string value = token.substr(index + 1, token.length());
        if (value == "") {
            throw "SYNTAX ERROR; COLUMN VALUES MUST NOT BE EMPTY STRINGS;";
        }

        columnValues[columnName] = value;
    }

    executionHandler.insert(columnValues);

    std::cout << "SUCCESS IN INSERTING ON TABLE: " << this->activeTable << ";" << std::endl;
}

void CommandParser::parseDelete(std::vector<std::string> tokens) {
    
}

void CommandParser::parseUpdate(std::vector<std::string> tokens) {
    
}