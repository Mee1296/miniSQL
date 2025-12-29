#pragma once
#include <vector>
#include "column.h"

struct Schema {
    std::string table_name;
    std::vector<Column> columns;

    size_t rowSize() const {
        size_t total = 0;
        for (auto& col : columns)
            total += columnStorageSize(col);
        return total;
    }
};
