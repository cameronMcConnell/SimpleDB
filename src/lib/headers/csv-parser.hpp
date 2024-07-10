#ifndef CSV_PARSER
#define CSV_PARSER

#include "errors.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <fstream> 
#include <iostream>
#include <sstream>

class CSVParser {
    private:
        std::vector<std::string> headers;

    public:
        CSVParser() = default;
        std::vector<std::string> getHeaders();
        std::vector<std::unordered_map<std::string, std::string>> loadTable(std::string tableName);
        std::string toCsvString(std::vector<std::unordered_map<std::string, std::string>> table);
};

#endif