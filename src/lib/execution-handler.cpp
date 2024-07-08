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

    //append to table here.
}

void ExecutionHandler::select(std::unordered_map<std::string, Predicate> conditions) {
    std::unordered_map<std::string, std::string> verifyRow = this->table[0];

    for (auto columnValuePair : conditions) {
        std::string header = columnValuePair.first;
        if (verifyRow.find(header) == verifyRow.end()) {
            std::string message = "SYNTAX ERROR; HEADER " + columnValuePair.first + " IS NOT PRESENT IN TABLE " + this->activeTable + ";";
            throw SyntaxError(message);
        }
    }

    std::vector<std::unordered_map<std::string, std::string>> selectRows;

    for (auto row : this->table) {
        for (auto columnValuePair : row) {
            std::string header = columnValuePair.first;
            
            if (conditions.find(header) != conditions.end()) {
                Operator op = conditions[header].op;
                std::string conditionsValue = conditions[header].value;
                std::string tableValue = row[header];
                
                if (op == Operator::EQUAL && tableValue == conditionsValue)
                    selectRows.push_back(row);
                else if (op == Operator::NOT_EQUAL && tableValue != conditionsValue)
                    selectRows.push_back(row);
                else if (op == Operator::LESS_THAN && tableValue < conditionsValue)
                    selectRows.push_back(row);
                else if (op == Operator::GREATER_THAN && tableValue > conditionsValue)
                    selectRows.push_back(row);
                else if (op == Operator::LESS_EQUAL && tableValue <= conditionsValue)
                    selectRows.push_back(row);
                else if (op == Operator::GREATER_EQUAL && tableValue >= conditionsValue)
                    selectRows.push_back(row);
            }
        }
    }

    std::string csvString = csvParser.toCsvString(selectRows);

    // Do stuff with string here.
}

void ExecutionHandler::selectAll() {
    std::string csvString = csvParser.toCsvString(this->table);

    // Do suff with string here.
}

void ExecutionHandler::delete_(std::unordered_map<std::string, Predicate> condtions) {
    
}

void ExecutionHandler::update(std::unordered_map<std::string, Predicate> conditions, std::unordered_map<std::string, std::string> statements) {

}

void ExecutionHandler::updateAll(std::unordered_map<std::string, std::string> statements) {

}