#include "headers/execution-handler.hpp"

ExecutionHandler::ExecutionHandler() {
    this->csvParser = CSVParser();
    this->activeTable = "root";
}

void ExecutionHandler::setActiveTable(std::string activeTable) {
    this->activeTable = activeTable;
    this->table = csvParser.loadTable(activeTable);
}

std::pair<std::vector<std::unordered_map<std::string, std::string>>, std::vector<std::unordered_map<std::string, std::string>>> ExecutionHandler::getSelectedAndUnselectedRows(std::unordered_map<std::string, Predicate> conditions) {
    std::unordered_map<std::string, std::string> verifyRow = this->table[0];

    for (auto headerValuePair : conditions) {
        std::string header = headerValuePair.first;
        if (verifyRow.find(header) == verifyRow.end()) {
            std::string message = "SYNTAX ERROR; HEADER " + header + " IS NOT PRESENT IN TABLE " + this->activeTable + ";";
            throw SyntaxError(message);
        }
    }

    std::vector<std::unordered_map<std::string, std::string>> selectedRows;
    std::vector<std::unordered_map<std::string, std::string>> unSelectedRows;

    for (auto row : this->table) {
        bool didSelectRow = false;
        for (auto headerValuePair : row) {
            std::string header = headerValuePair.first;
            if (conditions.find(header) != conditions.end()) {
                Operator op = conditions[header].op;
                std::string conditionsValue = conditions[header].value;
                std::string tableValue = row[header];

                if (op == Operator::EQUAL && tableValue == conditionsValue) {
                    selectedRows.push_back(row);
                    didSelectRow = true;
                    break;
                }
                else if (op == Operator::NOT_EQUAL && tableValue != conditionsValue) {
                    selectedRows.push_back(row);
                    didSelectRow = true;
                    break;
                }
                else if (op == Operator::LESS_THAN && tableValue < conditionsValue) {
                    selectedRows.push_back(row);
                    didSelectRow = true;
                    break;
                }
                else if (op == Operator::GREATER_THAN && tableValue > conditionsValue) {
                    selectedRows.push_back(row);
                    didSelectRow = true;
                    break;
                }
                else if (op == Operator::LESS_EQUAL && tableValue <= conditionsValue) {
                    selectedRows.push_back(row);
                    didSelectRow = true;
                    break;
                }
                else if (op == Operator::GREATER_EQUAL && tableValue >= conditionsValue) {
                    selectedRows.push_back(row);
                    didSelectRow = true;
                    break;
                }
            }
            if (!didSelectRow) {
                unSelectedRows.push_back(row);
            }
        }
    }

    return std::make_pair(selectedRows, unSelectedRows);
}

void ExecutionHandler::verifyStatementHeaders(std::unordered_map<std::string, std::string> statements) {
    std::unordered_map<std::string, std::string> verifyRow = this->table[0];

    for (auto headerValuePair : statements) {
        std::string header = headerValuePair.first;
        if (verifyRow.find(header) == verifyRow.end()) {
            std::string message = "SYNTAX ERROR; HEADER " + header + " IS NOT PRESENT IN TABLE " + this->activeTable + ";";
            throw SyntaxError(message);
        }
    }
}

void ExecutionHandler::updateRows(std::vector<std::unordered_map<std::string, std::string>> &rows, std::unordered_map<std::string, std::string> statements) {
    verifyStatementHeaders(statements);

    for (std::unordered_map<std::string, std::string> row : rows) {
        for (auto headerValuePair : statements) {
            std::string header = headerValuePair.first;
            std::string value = headerValuePair.second;
            row[header] = value;
        }
    }
}

void ExecutionHandler::create(std::string tableName, std::vector<std::string> headers) {
    // Figure this out.
}

void ExecutionHandler::drop(std::string tableName) {
    std::string path = "tables/" + tableName + ".csv";
    
    if (std::remove(path.c_str()) != 0) {
        std::string message = "ERROR DROPPING FILE " + path + ";";
        throw FileError(message);
    }
}

void ExecutionHandler::use(std::string tableName) {
    setActiveTable(tableName);
}

void ExecutionHandler::insert(std::unordered_map<std::string, std::string> statements) {
    
    verifyStatementHeaders(statements);

    this->table.push_back(statements);
    
    std::string csvString = csvParser.toCsvString(this->table);

    // Append to table here.
}

void ExecutionHandler::select(std::unordered_map<std::string, Predicate> conditions) {

    std::vector<std::unordered_map<std::string, std::string>> selectedRows = getSelectedAndUnselectedRows(conditions).first;

    std::string csvString = csvParser.toCsvString(selectedRows);

    // Do stuff with string here.
}

void ExecutionHandler::selectAll() {
    
    std::string csvString = csvParser.toCsvString(this->table);

    // Do suff with string here.
}

void ExecutionHandler::delete_(std::unordered_map<std::string, Predicate> conditions) {
    
    std::vector<std::unordered_map<std::string, std::string>> selectedRows = getSelectedAndUnselectedRows(conditions).first;

    // Overwrite table here.
}

void ExecutionHandler::update(std::unordered_map<std::string, Predicate> conditions, std::unordered_map<std::string, std::string> statements) {
    
    auto rows = getSelectedAndUnselectedRows(conditions);
    std::vector<std::unordered_map<std::string, std::string>> selectedRows = rows.first;
    std::vector<std::unordered_map<std::string, std::string>> unSelectedRows = rows.second;

    updateRows(selectedRows, statements);

    // Overwrite table here.
}

void ExecutionHandler::updateAll(std::unordered_map<std::string, std::string> statements) {
    
    updateRows(this->table, statements);
}