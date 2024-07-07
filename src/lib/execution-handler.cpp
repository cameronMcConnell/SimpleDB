#include "headers/execution-handler.hpp"

ExecutionHandler::ExecutionHandler() {
    this->csvParser = CSVParser();
    this->activeTable = "root";
}

void ExecutionHandler::setActiveTable(std::string activeTable) {
    this->activeTable = activeTable;
    this->table = csvParser.loadTable(activeTable);
}

void ExecutionHandler::create(std::string tableName, std::vector<std::string> headers) {

}

void ExecutionHandler::drop(std::string tableName) {
    
}

void ExecutionHandler::use(std::string tableName) {
    setActiveTable(tableName);
}

void ExecutionHandler::insert(std::unordered_map<std::string, std::string> statements) {
    std::unordered_map<std::string, std::string> verifyRow = this->table[0];

    for (auto columnValuePair : statements) {
        if (verifyRow.find(columnValuePair.first) == verifyRow.end()) {
            std::string message = "SYNTAX ERROR; HEADER " + columnValuePair.first + " IS NOT PRESENT IN TABLE " + this->activeTable + ";";
            throw SyntaxError(message);
        }
    }

    this->table.push_back(statements);
    
    std::string csvString = csvParser.toCsvString(this->table);

    writeTable(csvString);
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