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

Operator CommandParser::stringToOperator(std::string opStr) {
    if (opStr == "==") return Operator::EQUAL;
    if (opStr == "!=") return Operator::NOT_EQUAL;
    if (opStr == "<") return Operator::LESS_THAN;
    if (opStr == ">") return Operator::GREATER_THAN;
    if (opStr == "<=") return Operator::LESS_EQUAL;
    if (opStr == ">=") return Operator::GREATER_EQUAL;
    return Operator::INVALID;
}

std::string CommandParser::getActiveTable() {
    return this->activeTable;
}

void CommandParser::parseCommand(std::string command) {
    try {
        std::vector<std::string> tokens = tokenize(command);

        if (tokens.empty()) {
            std::cout << "SYNTAX ERROR; NO COMMAND SUPPLIED;" << std::endl;
        }
        else if (tokens[0] == "CREATE") {
            checkForValidSize(tokens, 4);
            parseCreate(tokens);
        }
        else if (tokens[0] == "DROP") {
            checkForValidSize(tokens, 2);
            parseDrop(tokens);
        }
        else if (tokens[0] == "USE") {
            checkForValidSize(tokens, 2);
            parseUse(tokens);
        }
        else if (tokens[0] == "SELECT") {
            if (this->activeTable == "root") {
                throw "NO ACTIVE TABLE IS IN USE;";
            }
            checkForValidSize(tokens, 2);
            parseSelect(tokens);
        }
        else if (tokens[0] == "INSERT") {
            if (this->activeTable == "root") {
                throw "NO ACTIVE TABLE IS IN USE;";
            }
            checkForValidSize(tokens, 2);
            parseInsert(tokens);
        }
        else if (tokens[0] == "DELETE") {
    
        }
        else if (tokens[0] == "UPDATE") {
    
        }
        else {
            std::cout << "SYNTAX ERROR; INVALID TOKEN: " << tokens[0] << ";" << std::endl; 
        }
    }
    catch (const char *message) {
        std::cout << message << std::endl;
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
        if (header.empty()){
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
    if (tokens[1] == "*") {
        executionHandler.selectAll();
    }
    else {
        std::unordered_map<std::string, Condition> conditions;
        std::regex conditionRegex(R"((\w+)(==|!=|<|>|<=|>=)([^,]+),)");
        std::sregex_iterator iter(tokens[1].begin(), tokens[1].end(), conditionRegex);
        std::sregex_iterator end;

        while (iter != end) {
            std::smatch match = *iter;
            std::string columnName = match[1].str();
            std::string opStr = match[2].str();
            std::string value = match[3].str();

            Operator op = stringToOperator(opStr);
            if (op == Operator::INVALID) {
                throw "SYNTAX ERROR; OPERATOR IS INVALID;";
            }

            conditions[columnName] = {op, value};
            iter++;
        }

        executionHandler.select(conditions);
    }

    std::cout << "SUCCESS IN SELECTING FROM TABLE: " << this->activeTable << ";" << std::endl;
}

void CommandParser::parseInsert(std::vector<std::string> tokens) {
    std::unordered_map<std::string, std::string> columnValues;
    
    std::string token;
    const char delimeter = ',';
    std::istringstream iss(tokens[1]);

    while (std::getline(iss, token, delimeter)) {
        if (token.empty()) {
            throw "SYNTAX ERROR; COLUMN VALUES MUST NOT CONTAIN EMPTY STRINGS;";
        }

        size_t index = token.find('=');
        if (index == std::string::npos) {
            throw "SYNTAX ERROR; COLUMN VALUES MUST INCLUDE =;";
        }

        std::string columnName = token.substr(0, index);
        if (columnName.empty()) {
            throw "SYNTAX ERROR; COLUMN NAMES MUST NOT BE EMPTY STRINGS;";
        }

        std::string value = token.substr(index + 1, token.length());
        if (value.empty()) {
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