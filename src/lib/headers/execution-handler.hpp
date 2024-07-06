#ifndef EXECUTION_HANDLER
#define EXECUTION_HANDLER

#include "expressions.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class ExecutionHandler {
    private:
        
    public:
        ExecutionHandler();

        void create(std::string tableName, std::vector<std::string> headers);
        void drop(std::string tableName);
        void use(std::string tableName);
        void insert(std::unordered_map<std::string, std::string> statements);
        void select(std::unordered_map<std::string, Predicate> conditions);
        void selectAll();
        void delete_(std::unordered_map<std::string, Predicate> condtions);
        void update(std::unordered_map<std::string, Predicate> conditions, std::unordered_map<std::string, std::string> statements);
        void updateAll(std::unordered_map<std::string, std::string> statements);
};

#endif