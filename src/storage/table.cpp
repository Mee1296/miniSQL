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
    
    if (!in) return rows;

    in.seekg(0, std::ios::end);
    size_t fileSize = in.tellg();
    in.seekg(0);

    if (fileSize % rowSize != 0)
        throw std::runtime_error("Corrupted table file");

    size_t rowCount = fileSize / rowSize;

    for (size_t i = 0; i < rowCount; i++) {
        Row r(rowSize);
        in.read((char*)r.data(), rowSize);
        rows.push_back(r);
    }

    return rows;
}
