#pragma once
#include <string>

enum class ColumnType {
    INT,
    TEXT,
    DOUBLE,
    BOOLEAN
};

inline size_t typeSize(ColumnType t, size_t text_len = 0) {
    switch (t) {
        case ColumnType::INT:  return sizeof(int);
        case ColumnType::TEXT: return text_len;
        case ColumnType::DOUBLE: return sizeof(double);
        case ColumnType::BOOLEAN: return sizeof(bool);
    }
    return 0;
}
