#pragma once
#include <string>

enum class ColumnType {
    INT,
    TEXT,
    DOUBLE,
    BOOLEAN
};

inline size_t columnStorageSize(const Column& col) {
    switch (col.type) {
    case ColumnType::INT:     return 4;
    case ColumnType::DOUBLE:  return 8;
    case ColumnType::BOOLEAN: return 1;   
    case ColumnType::TEXT:    return col.size;
    }
    return 0;
}
