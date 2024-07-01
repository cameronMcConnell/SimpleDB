#ifndef EXECUTION_HANDLER
#define EXECUTION_HANDLER

#include <string>
#include <vector>

class ExecutionHandler {
    public:
        ExecutionHandler();
        void create(std::string tableName, std::vector<std::string> headers);
        void drop(std::string tableName);
};

#endif