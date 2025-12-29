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
                std::cout << v << "\t";
                offset += sizeof(int);
            }
            else if( col.type == ColumnType::TEXT) {
                std::string s(
                    (char*)row.data() + offset,
                    col.size
                );
                std::cout << s.c_str() << "\t";
                offset += col.size;
            }else if(col.type == ColumnType::DOUBLE){
                double v;
                std::memcpy(&v, row.data() + offset, sizeof(double));
                std::cout << v << "\t";
                offset += sizeof(double);
            }else if(col.type == ColumnType::BOOLEAN){
                uint8_t v = row.data()[offset];
                std::cout << (v ? "true" : "false") << "\t";
                offset += 1;
            }
        }
        std::cout << "\n";
    }
};
