#pragma once
#include "types.h"
#include <string>

struct Column {
  std::string name;
  ColumnType type;
  size_t size; // for TEXT

  size_t storageSize() const {
    switch (type) {
    case ColumnType::INT:
      return 4;
    case ColumnType::DOUBLE:
      return 8;
    case ColumnType::BOOLEAN:
      return 1;
    case ColumnType::TEXT:
      return size;
    }
    return 0;
  }
};
