#include "command/commandExecutor.h"

#include "catalog/catalog.h"
#include "storage/row_builder.h"
#include "storage/row_reader.h"
#include "storage/schema_io.h"
#include "storage/table.h"
#include "util/fs.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

static std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string CommandExecutor::trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \t");
  if (first == std::string::npos)
    return "";
  size_t last = str.find_last_not_of(" \t");
  return str.substr(first, last - first + 1);
}

void CommandExecutor::run() {
  std::cout << "Welcome to miniSQL v1.0\nEnter \\q to quit\n";
  std::string line;

  while (true) {
    std::cout << "miniSQL> ";
    if (!std::getline(std::cin, line))
      break;

    if (line == "\\q") {
      std::cout << "Goodbye!\n";
      break;
    }

    if (!line.empty())
      execute(line);
  }
}

void CommandExecutor::execute(const std::string &line) {
  if (line.rfind("SHOW TABLE", 0) == 0) {
    handleShowTables();
  } else if (line.rfind("CREATE TABLE", 0) == 0) {
    handleCreateTable(line);
  } else if (line.rfind("DROP TABLE", 0) == 0) {
    handleDropTable(line);
  } else if (line.rfind("INSERT INTO", 0) == 0) {
    handleInsert(line);
  } else if (line.rfind("SELECT", 0) == 0) {
    handleSelect(line);
  } else {
    std::cout << "Unknown command: " << line << "\n";
  }
}

void CommandExecutor::handleCreateTable(const std::string &command) {
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

  for (auto &def : split(columnsPart, ',')) {
    std::stringstream ss(trim(def));
    std::string name, type;
    ss >> name >> type;

    Column col;
    col.name = name;

    if (type == "INT")
      col.type = ColumnType::INT;
    else if (type == "DOUBLE")
      col.type = ColumnType::DOUBLE;
    else if (type == "TEXT") {
      col.type = ColumnType::TEXT;
      col.size = 255;
    }else if( type == "BOOLEAN"){
      col.type = ColumnType::BOOLEAN;
    } else {
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

void CommandExecutor::handleDropTable(const std::string &command) {
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
  for (auto &t : tables)
    std::cout << "- " << t << "\n";
}

void CommandExecutor::handleInsert(const std::string &command) {
  size_t valuesPos = command.find("VALUES");
  if (valuesPos == std::string::npos) {
    std::cout << "Usage: INSERT INTO <table> VALUES (...)\n";
    return;
  }

  std::string tableName = trim(command.substr(12, valuesPos - 12));
  if (!catalogExists(tableName)) {
    std::cout << "Table " << tableName << " does not exist\n";
    return;
  }

  size_t openParen = command.find('(', valuesPos);
  size_t closeParen = command.find(')', openParen);

  if (openParen == std::string::npos || closeParen == std::string::npos) {
    std::cout << "Invalid syntax\n";
    return;
  }

  std::string valuesPart =
      command.substr(openParen + 1, closeParen - openParen - 1);
  std::vector<std::string> values;
  for (auto &val : split(valuesPart, ',')) {
    values.push_back(trim(val));
  }

  try {
    Schema schema = readSchema("data/" + tableName + "/schema.meta");
    if (values.size() != schema.columns.size()) {
      std::cout << "Column count mismatch\n";
      return;
    }

    Row row = RowBuilder::build(schema, values);
    appendRow("data/" + tableName + "/data.bin", row);
    std::cout << "1 row inserted\n";
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << "\n";
  }
}

void CommandExecutor::handleSelect(const std::string &command) {
  size_t fromPos = command.find("FROM");
  if (fromPos == std::string::npos) {
    std::cout << "Usage: SELECT * FROM <table>\n";
    return;
  }

  std::string columnsPart = trim(command.substr(7, fromPos - 7));
  if (columnsPart != "*") {
    std::cout << "Only SELECT * is supported\n";
    return;
  }

  std::string tableName = trim(command.substr(fromPos + 5));
  if (!catalogExists(tableName)) {
    std::cout << "Table " << tableName << " does not exist\n";
    return;
  }

  try {
    Schema schema = readSchema("data/" + tableName + "/schema.meta");
    printSchema(schema);
    std::vector<Row> rows =
        readAllRows("data/" + tableName + "/data.bin", schema);

    for (const auto &row : rows) {
      RowReader::print(schema, row);
    }
    std::cout << "(" << rows.size() << " rows)\n";
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << "\n";
  }
}
