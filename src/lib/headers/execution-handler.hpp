#ifndef EXECUTION_HANDLER
#define EXECUTION_HANDLER

#include "csv-parser.hpp"
#include "expressions.hpp"
#include "errors.hpp"

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <cstdio>

class ExecutionHandler {
    private:
        CSVParser csvParser;
        std::string activeTable;
        std::vector<std::unordered_map<std::string, std::string>> table;
        std::pair<std::vector<std::unordered_map<std::string, std::string>>, std::vector<std::unordered_map<std::string, std::string>>> getSelectedAndUnselectedRows(std::unordered_map<std::string, Predicate> conditions);
        void updateRows(std::vector<std::unordered_map<std::string, std::string>> &rows, std::unordered_map<std::string, std::string> statements);
        void verifyStatementHeaders(std::unordered_map<std::string, std::string> statements);

    public:
        ExecutionHandler();
        void setActiveTable(std::string activeTable);
        void create(std::string tableName, std::vector<std::string> headers);
        void drop(std::string tableName);
        void use(std::string tableName);
        void insert(std::unordered_map<std::string, std::string> statements);
        void select(std::unordered_map<std::string, Predicate> conditions);
        void selectAll();
        void delete_(std::unordered_map<std::string, Predicate> conditions);
        void update(std::unordered_map<std::string, Predicate> conditions, std::unordered_map<std::string, std::string> statements);
        void updateAll(std::unordered_map<std::string, std::string> statements);
};

#endif