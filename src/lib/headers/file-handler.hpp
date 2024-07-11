#ifndef FILE_HANDLER
#define FILE_HANDLER

#include "errors.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>

class FileHandler {
    public:
        FileHandler() = default;
        void checkIfFileExists(std::string path);
        void writeTable(std::string path, std::string csvString);
        void removeTable(std::string path);
};

#endif
