#ifndef EXECUTION_HANDLER
#define EXECUTION_HANDLER

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
        void insert(std::unordered_map<std::string, std::string> columnValues);
        void select(std::unordered_map<std::string, std::string> map);
        void selectAll();
};

#endif