#include "headers/csv-parser.hpp"

std::vector<std::string> CSVParser::getHeaders() {
    return this->headers;
}

std::vector<std::unordered_map<std::string, std::string>> CSVParser::loadTable(std::string tableName) {
    std::string fileName = "tables/" + tableName + ".csv";
    std::ifstream csvFile(fileName, std::ios::in);

    std::vector<std::unordered_map<std::string, std::string>> table;
    std::vector<std::string> headers;
    const char delimeter = ' ';
    bool readingHeader = true;
    std::string line;

    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            if (readingHeader) {
                readingHeader = false;
                std::string header;
                std::istringstream iss(line);
                
                while (std::getline(iss, header, delimeter)) {
                    headers.push_back(header);
                }

                this->headers = headers;
            }
            else {
                std::unordered_map<std::string, std::string> newRow;
                std::string value;
                int headerIndex = 0;
                std::istringstream iss(line);

                while (std::getline(iss, value, delimeter)) {
                    newRow[headers[headerIndex]] = value;
                    ++headerIndex;
                }

                table.push_back(newRow);
            }
        }
    } else {
        std::string message = "ERROR OPENING FILE " + fileName + ";";
        throw FileError(message);
    }

    return table;
}

std::string CSVParser::toCsvString(std::vector<std::unordered_map<std::string, std::string>> table) {
    std::string csvString;
    
    std::ostringstream oss;
    for (size_t i = 0; i < this->headers.size(); ++i) {
        if (i != 0) {
            oss << ",";
        }
        oss << this->headers[i];
    }

    oss << "\n";
    csvString += oss.str();
    oss.str("");

    for (std::unordered_map<std::string, std::string> row : table) {
        for (size_t i = 0; i < this->headers.size(); ++i) {
            std::string header = this->headers[i];
            if (i != 0) {
                oss << ",";
            }
            oss << row[header];
        }

        oss << "\n";
        csvString += oss.str();
        oss.str("");
    }

    return csvString;
}