#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include "execution-handler.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


class CommandParser {
    private:
        ExecutionHandler executionHandler;

        std::vector<std::string> tokenize(std::string command);

        void checkForValidSize(std::vector<std::string> tokens, size_t size);
        
        void parseCreate(std::vector<std::string> tokens);
        void parseDrop(std::vector<std::string> tokens);
        void parseUse(std::vector<std::string> tokens);
        void parseSelect(std::vector<std::string> tokens);
        void parseInsert(std::vector<std::string> tokens);
        void parseDelete(std::vector<std::string> tokens);
        void parseUpdate(std::vector<std::string> tokens);
        
    public:
        CommandParser();
        void parseCommand(std::string command);
};

#endif