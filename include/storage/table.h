#pragma once
#include "storage/row.h"
#include "storage/schema.h"
#include <string>
#include <vector>

void appendRow(const std::string& path, const Row& row);
std::vector<Row> readAllRows(const std::string& path, const Schema& schema);
