#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include "execution-handler.hpp"
#include "expressions.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <regex>

class CommandParser {
    private:
        std::vector<std::string> tokenize(std::string command);
        void checkForValidSize(std::vector<std::string> tokens, size_t size);
        Operator stringToOperator(std::string opStr);

        void parseCreate(std::vector<std::string> tokens);
        void parseDrop(std::vector<std::string> tokens);
        void parseUse(std::vector<std::string> tokens);
        void parseSelect(std::vector<std::string> tokens);
        void parseInsert(std::vector<std::string> tokens);
        void parseDelete(std::vector<std::string> tokens);
        void parseUpdate(std::vector<std::string> tokens);
        
        ExecutionHandler executionHandler;
        std::string activeTable;
    public:
        CommandParser(std::string activeTable);
        void parseCommand(std::string command);
        std::string getActiveTable();
};

#endif