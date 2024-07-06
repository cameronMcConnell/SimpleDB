#ifndef CSV_PARSER
#define CSV_PARSER

#include <vector>
#include <unordered_map>
#include <string>

class CSVParser {
    public:
        CSVParser();
        std::vector<std::unordered_map<std::string, std::string>> loadTable(std::string tableName);
};

#endif