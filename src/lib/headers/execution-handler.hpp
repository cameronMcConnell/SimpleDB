#ifndef EXECUTION_HANDLER
#define EXECUTION_HANDLER

#include "csv-parser.hpp"
#include "expressions.hpp"
#include "file-handler.hpp"
#include "errors.hpp"

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <set>
#include <cstdio>

class ExecutionHandler {
    private:
        CSVParser csvParser;
        FileHandler fileHandler;
        std::string activeTable;
        std::vector<std::unordered_map<std::string, std::string>> table;
        std::pair<std::vector<std::unordered_map<std::string, std::string>>, std::vector<std::unordered_map<std::string, std::string>>> getSelectedAndUnselectedRows(std::unordered_map<std::string, std::vector<Predicate>> conditions);
        void updateRows(std::vector<std::unordered_map<std::string, std::string>> &rows, std::unordered_map<std::string, std::string> statements);
        void verifyStatementHeaders(std::unordered_map<std::string, std::string> statements);
        void combineRows(std::vector<std::unordered_map<std::string, std::string>> &rows1, std::vector<std::unordered_map<std::string, std::string>> rows2);

    public:
        ExecutionHandler();
        void setActiveTable(std::string activeTable);
        void create(std::string tableName, std::vector<std::string> headers);
        void drop(std::string tableName);
        void use(std::string tableName);
        void insert(std::unordered_map<std::string, std::string> statements);
        std::string select(std::unordered_map<std::string, std::vector<Predicate>> conditions);
        std::string selectAll();
        void delete_(std::unordered_map<std::string, std::vector<Predicate>> conditions);
        void update(std::unordered_map<std::string, std::vector<Predicate>> conditions, std::unordered_map<std::string, std::string> statements);
        void updateAll(std::unordered_map<std::string, std::string> statements);
};

#endif