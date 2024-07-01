#ifndef EXECUTION_HANDLER
#define EXECUTION_HANDLER

#include <string>

class ExecutionHandler {
    public:
        ExecutionHandler();
        void create(std::string tableName);
        void drop(std::string tableName);
};

#endif