#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include "execution-handler.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <deque>


class CommandParser {
    private:
        ExecutionHandler executionHandler;

        std::deque<std::string> tokenize(std::string command);
        
        void checkForEmptyTokens(std::deque<std::string> tokens);
        void checkForValidSize(std::deque<std::string> tokens, size_t size);
        
        void parseCreate(std::deque<std::string> tokens);
        void parseDrop(std::deque<std::string> tokens);
        void parseUse(std::deque<std::string> tokens);
        void parseSelect(std::string command);
        void parseInsert(std::string command);
        void parseDelete(std::string command);
        void parseUpdate(std::string command);
        
    public:
        CommandParser();
        void parseCommand(std::string command);
};

#endif