#include "headers/file-handler.hpp"

void FileHandler::checkIfFileExists(std::string path) {
    const char* dir = path.c_str();
    struct stat sb;
    
    if (stat(dir, &sb) != 0) {
        std::string message = "FILE ERROR; FILE " + path + " DOES NOT EXIST;";
        throw FileError(message);
    }
}

void FileHandler::writeTable(std::string path, std::string csvString) {
    std::ofstream ofs(path, std::ios::trunc);
    if (!ofs) {
        std::string message = "FILE ERROR; ERROR OPENING FILE " + path + ";";
        throw FileError(message);
    }

    ofs << csvString;
    ofs.close();
}

void FileHandler::removeTable(std::string path) {
    if (std::remove(path.c_str()) != 0) {
        std::string message = "FILE ERROR; ERROR DROPPING FILE " + path + ";";
        throw FileError(message);
    }
}
