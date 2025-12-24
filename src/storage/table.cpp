#include "storage/row.h"
#include "storage/schema.h"
#include <fstream>

void appendRow(const std::string& path, const Row& row) {
    std::ofstream out(path, std::ios::binary | std::ios::app);
    out.write((char*)row.data(), row.size());
}

std::vector<Row> readAllRows(
    const std::string& path,
    const Schema& schema
) {
    std::ifstream in(path, std::ios::binary);
    std::vector<Row> rows;

    size_t rowSize = schema.rowSize();
    while (true) {
        Row r(rowSize);
        in.read((char*)r.data(), rowSize);
        if (!in) break;
        rows.push_back(r);
    }
    return rows;
}
