#pragma once
#include "schema.h"
#include "row.h"
#include <cstring>

class RowBuilder {
public:
    static Row build(
        const Schema& schema,
        const std::vector<std::string>& values
    ) {
        Row row(schema.rowSize());
        size_t offset = 0;

        for (size_t i = 0; i < schema.columns.size(); i++) {
            const auto& col = schema.columns[i];

            if (col.type == ColumnType::INT) {
                int v = std::stoi(values[i]);
                std::memcpy(row.data() + offset, &v, sizeof(int));
                offset += sizeof(int);
            }
            else if (col.type == ColumnType::TEXT) {
                std::memset(row.data() + offset, 0, col.size);
                std::memcpy(row.data() + offset, values[i].c_str(),
                            std::min(col.size, values[i].size()));
                offset += col.size;
            }
        }
        return row;
    }
};
