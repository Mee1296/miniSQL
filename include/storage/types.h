#pragma once
#include <string>

enum class ColumnType {
    INT,
    TEXT
};

inline size_t typeSize(ColumnType t, size_t text_len = 0) {
    switch (t) {
        case ColumnType::INT:  return sizeof(int);
        case ColumnType::TEXT: return text_len;
    }
    return 0;
}
