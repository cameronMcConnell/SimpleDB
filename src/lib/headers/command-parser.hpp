#ifndef COMMAND_PARSER
#define COMMAND_PARSER

#include "execution-handler.hpp";
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class CommandParser {
    private:
        ExecutionHandler executionHandler;
        void parseCreate(std::string command);
        void parseDrop(std::string command);
        void parseSelect(std::string command);
        void parseInsert(std::string command);
        void parseDelete(std::string command);
        void parseUpdate(std::string command);
        
    public:
        CommandParser();
        void parseCommand(std::string command);
};

#endif