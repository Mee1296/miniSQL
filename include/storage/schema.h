#pragma once
#include "column.h"
#include <vector>

struct Schema {
  std::string table_name;
  std::vector<Column> columns;

  size_t rowSize() const {
    size_t total = 0;
    for (auto &col : columns)
      total += col.storageSize();
    return total;
  }
};
