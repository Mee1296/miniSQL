#pragma once
#include "types.h"

struct Column {
    std::string name;
    ColumnType type;
    size_t size;   // for TEXT
};
