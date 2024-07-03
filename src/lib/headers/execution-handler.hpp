#ifndef EXECUTION_HANDLER
#define EXECUTION_HANDLER

#include <string>
#include <vector>

class ExecutionHandler {
    private:

    public:
        ExecutionHandler();
        void create(std::string tableName, std::vector<std::string> headers);
        void drop(std::string tableName);
        void use(std::string tableName);
};

#endif