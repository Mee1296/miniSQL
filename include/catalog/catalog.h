#pragma once
#include <string>
#include <vector>

void catalogAddTable(const std::string& table);
std::vector<std::string> catalogListTables();
bool catalogExists(const std::string& table);
bool catalogRemoveTable(const std::string& table);