#include "headers/command-parser.hpp"

CommandParser::CommandParser() {
    this->executionHandler = ExecutionHandler();
    this->activeTable = "root";
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
        throw SyntaxError("SYNTAX ERROR; INVALID COMMAND;");
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

std::unordered_map<std::string, std::vector<Predicate>> CommandParser::parseCondtions(std::string conditions) {
        std::unordered_map<std::string, std::vector<Predicate>> conditionsMap;
        std::regex conditionRegex(R"((\w+)(==|!=|<|>|<=|>=)(\w+)(?:,|$))");
        std::sregex_iterator iter(conditions.begin(), conditions.end(), conditionRegex);
        std::sregex_iterator end = std::sregex_iterator();

        while (iter != end) {
            std::smatch match = *iter;
            std::string columnName = match[1].str();
            std::string opStr = match[2].str();
            std::string value = match[3].str();

            Operator op = stringToOperator(opStr);
            if (op == Operator::INVALID) {
                throw SyntaxError("SYNTAX ERROR; OPERATOR IS INVALID;");
            }

            conditionsMap[columnName].push_back({op, value});
            ++iter;
        }

        return conditionsMap;
}

std::unordered_map<std::string, std::string> CommandParser::parseStatements(std::string statements) {
    std::unordered_map<std::string, std::string> statementsMap;
    
    std::string token;
    const char delimeter = ',';
    std::istringstream iss(statements);

    while (std::getline(iss, token, delimeter)) {
        if (token.empty()) {
            throw SyntaxError("SYNTAX ERROR; COLUMN VALUES MUST NOT CONTAIN EMPTY STRINGS;");
        }

        size_t index = token.find('=');
        if (index == std::string::npos) {
            throw SyntaxError("SYNTAX ERROR; COLUMN VALUES MUST INCLUDE =;");
        }

        std::string columnName = token.substr(0, index);
        if (columnName.empty()) {
            throw SyntaxError("SYNTAX ERROR; COLUMN NAMES MUST NOT BE EMPTY STRINGS;");
        }

        std::string value = token.substr(index + 1, token.length());
        if (value.empty()) {
            throw SyntaxError("SYNTAX ERROR; COLUMN VALUES MUST NOT BE EMPTY STRINGS;");
        }

        statementsMap[columnName] = value;
    }

    return statementsMap;
}

std::vector<std::string> CommandParser::parseHeaders(std::string headers) {
    std::vector<std::string> headersVector;
    std::string header;
    const char delimeter = ',';
    std::istringstream iss(headers);

    while (std::getline(iss, header, delimeter)) {
        if (header.empty()){
            throw SyntaxError("SYNTAX ERROR; HEADERS MUST NOT CONTAIN EMPTY STRINGS;");
        }

        headersVector.push_back(header);
    }

    return headersVector;
}

std::string CommandParser::getActiveTable() {
    return this->activeTable;
}

void CommandParser::ensureActiveTable() {
    if (this->activeTable == "root") {
        throw SyntaxError("NO ACTIVE TABLE IS IN USE;");
    }
}

std::string CommandParser::parseCommand(std::string command) {
    std::vector<std::string> tokens = tokenize(command);

    if (tokens.empty()) {
        throw SyntaxError("SYNTAX ERROR; NO COMMAND SUPPLIED;");
    }
    else if (tokens[0] == "CREATE") {
        checkForValidSize(tokens, 4);
        return parseCreate(tokens);
    }
    else if (tokens[0] == "DROP") {
        checkForValidSize(tokens, 2);
        return parseDrop(tokens);
    }
    else if (tokens[0] == "USE") {
        checkForValidSize(tokens, 2);
        return parseUse(tokens);
    }
    else if (tokens[0] == "SELECT") {
        ensureActiveTable();
        checkForValidSize(tokens, 2);
        return parseSelect(tokens);
    }
    else if (tokens[0] == "INSERT") {
        ensureActiveTable();
        checkForValidSize(tokens, 2);
        return parseInsert(tokens);
    }
    else if (tokens[0] == "DELETE") {
        ensureActiveTable();
        checkForValidSize(tokens, 2);
        return parseDelete(tokens);
    }
    else if (tokens[0] == "UPDATE") {
        ensureActiveTable();
        checkForValidSize(tokens, 4);
        return parseUpdate(tokens);
    }
    else {
        std::string message = "SYNTAX ERROR; INVALID TOKEN: " + tokens[0] + ";";
        throw SyntaxError(message); 
    }
}

std::string CommandParser::parseCreate(std::vector<std::string> tokens) {
    std::string tableName = tokens[1];

    if (tokens[2] != "WITH") {
        throw SyntaxError("SYNTAX ERROR; WITH NOT INCLUDED;");
    }

    std::vector<std::string> headers = parseHeaders(tokens[3]);

    executionHandler.create(tableName, headers);

    std::string result = "SUCCESS IN CREATING TABLE: " + tableName + ";";
    return result;
}

std::string CommandParser::parseDrop(std::vector<std::string> tokens) {
    std::string tableName = tokens[1];

    executionHandler.drop(tableName);

    if (tableName == this->activeTable) {
        this->activeTable = "root";
        executionHandler.setActiveTable("root");
    }

    std::string result = "SUCCESS IN DROPPING TABLE: " + tableName + ";";
    return result;
}

std::string CommandParser::parseUse(std::vector<std::string> tokens) {
    std::string tableName = tokens[1];

    executionHandler.use(tableName);

    this->activeTable = tableName;
    executionHandler.setActiveTable(tableName);


    std::string result = "SUCCESS IN USING TABLE: " + tableName + ";";
    return result;
}

std::string CommandParser::parseSelect(std::vector<std::string> tokens) {
    if (tokens[1] == "*") {
        return executionHandler.selectAll();
    }
    else {
        std::unordered_map<std::string, std::vector<Predicate>> conditions = parseCondtions(tokens[1]);

        return executionHandler.select(conditions);
    }
}

std::string CommandParser::parseInsert(std::vector<std::string> tokens) {
    std::unordered_map<std::string, std::string> statements = parseStatements(tokens[1]);

    executionHandler.insert(statements);

    std::string result = "SUCCESS IN INSERTING ON TABLE: " + this->activeTable + ";";
    return result;
}

std::string CommandParser::parseDelete(std::vector<std::string> tokens) {
    std::unordered_map<std::string, std::vector<Predicate>> conditions = parseCondtions(tokens[1]);

    executionHandler.delete_(conditions);

    std::string result = "SUCCESS IN DELETING ON TABLE: " + this->activeTable + ";";
    return result;
}

std::string CommandParser::parseUpdate(std::vector<std::string> tokens) {
    if (tokens[2] != "WITH") {
        throw SyntaxError("SYNTAX ERROR; WITH NOT INCLUDED;");
    }
    
    if (tokens[1]== "*") {
        std::unordered_map<std::string, std::string> statements = parseStatements(tokens[3]);

        executionHandler.updateAll(statements);
    }
    else {
        std::unordered_map<std::string, std::vector<Predicate>> conditions = parseCondtions(tokens[1]);

        std::unordered_map<std::string, std::string> statements = parseStatements(tokens[3]);

        executionHandler.update(conditions, statements);
    }

    std::string result = "SUCCESS IN UPDATING ON TABLE: " + this->activeTable + ";";
    return result;
}