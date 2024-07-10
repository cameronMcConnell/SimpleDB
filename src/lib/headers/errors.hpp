#ifndef ERRORS
#define ERRORS

#include <exception>
#include <string>

class SocketError : public std::exception {
    public:
        SocketError(const std::string& message) : message(message) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
    
    private:
        std::string message;
};

class FileError : public std::exception {
    public:
        FileError(const std::string& message) : message(message) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
    
    private:
        std::string message;
};

class SyntaxError : public std::exception {
public:
    SyntaxError(const std::string& message) : message(message) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
    
private:
    std::string message;
};

#endif