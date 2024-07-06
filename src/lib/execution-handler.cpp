#include "headers/execution-handler.hpp"

ExecutionHandler::ExecutionHandler() {
    
}

void ExecutionHandler::create(std::string tableName, std::vector<std::string> headers) {

}

void ExecutionHandler::drop(std::string tableName) {

}

void ExecutionHandler::use(std::string tableName) {

}

void ExecutionHandler::insert(std::unordered_map<std::string, std::string> statements) {

}

void ExecutionHandler::select(std::unordered_map<std::string, Predicate> conditions) {
    
}

void ExecutionHandler::selectAll() {
    
}

void ExecutionHandler::delete_(std::unordered_map<std::string, Predicate> condtions) {

}

void ExecutionHandler::update(std::unordered_map<std::string, Predicate> conditions, std::unordered_map<std::string, std::string> statements) {

}

void ExecutionHandler::updateAll(std::unordered_map<std::string, std::string> statements) {

}