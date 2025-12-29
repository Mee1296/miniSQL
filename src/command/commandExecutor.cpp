#include "command/commandExecutor.h"

#include "catalog/catalog.h"
#include "storage/schema_io.h"
#include "util/fs.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

static std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string CommandExecutor::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

void CommandExecutor::run() {
    std::cout << "Welcome to miniSQL v1.0\nEnter \\q to quit\n";
    std::string line;

    while (true) {
        std::cout << "miniSQL> ";
        if (!std::getline(std::cin, line)) break;

        if (line == "\\q") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (!line.empty())
            execute(line);
    }
}

void CommandExecutor::execute(const std::string& line) {
    if (line.rfind("SHOW TABLE", 0) == 0) {
        handleShowTables();
    }
    else if (line.rfind("CREATE TABLE", 0) == 0) {
        handleCreateTable(line);
    }
    else if (line.rfind("DROP TABLE", 0) == 0) {
        handleDropTable(line);
    }
    else {
        std::cout << "Unknown command: " << line << "\n";
    }
}

void CommandExecutor::handleCreateTable(const std::string& command) {
    size_t openParen = command.find('(');
    size_t closeParen = command.find(')');

    if (openParen == std::string::npos || closeParen < openParen) {
        std::cout << "Usage: CREATE TABLE <name> (...)\n";
        return;
    }

    std::string tableName =
        trim(command.substr(std::string("CREATE TABLE").length(),
                             openParen - std::string("CREATE TABLE").length()));

    if (tableName.empty()) {
        std::cout << "Invalid table name\n";
        return;
    }

    if (catalogExists(tableName)) {
        std::cout << "Table already exists\n";
        return;
    }

    std::string columnsPart =
        command.substr(openParen + 1, closeParen - openParen - 1);

    Schema schema;
    schema.table_name = tableName;

    for (auto& def : split(columnsPart, ',')) {
        std::stringstream ss(trim(def));
        std::string name, type;
        ss >> name >> type;

        Column col;
        col.name = name;

        if (type == "INT") col.type = ColumnType::INT;
        else if (type == "DOUBLE") col.type = ColumnType::DOUBLE;
        else if (type == "TEXT") {
            col.type = ColumnType::TEXT;
            col.size = 255;
        }
        else {
            std::cout << "Unknown type: " << type << "\n";
            return;
        }

        schema.columns.push_back(col);
    }

    createTableDir(tableName);
    writeSchema(schema, "data/" + tableName + "/schema.meta");
    catalogAddTable(tableName);

    std::cout << "Table " << tableName << " created\n";
}

void CommandExecutor::handleDropTable(const std::string& command) {
    std::string tableName =
        trim(command.substr(std::string("DROP TABLE").length()));

    if (tableName.empty()) {
        std::cout << "Invalid table name\n";
        return;
    }

    if (!catalogExists(tableName)) {
        std::cout << "Table does not exist\n";
        return;
    }

    catalogRemoveTable(tableName);
    std::cout << "Table " << tableName << " dropped\n";
}

void CommandExecutor::handleShowTables() {
    auto tables = catalogListTables();
    std::cout << "Tables:\n";
    for (auto& t : tables)
        std::cout << "- " << t << "\n";
}
