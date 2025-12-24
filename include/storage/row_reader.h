#pragma once
#include "schema.h"
#include "row.h"
#include <iostream>
#include <cstring>

class RowReader {
public:
    static void print(const Schema& schema, const Row& row) {
        size_t offset = 0;

        for (const auto& col : schema.columns) {
            if (col.type == ColumnType::INT) {
                int v;
                std::memcpy(&v, row.data() + offset, sizeof(int));
                std::cout << v << " ";
                offset += sizeof(int);
            }
            else {
                std::string s(
                    (char*)row.data() + offset,
                    col.size
                );
                std::cout << s.c_str() << " ";
                offset += col.size;
            }
        }
        std::cout << "\n";
    }
};
