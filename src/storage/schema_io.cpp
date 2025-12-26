#include "storage/schema.h"
#include <fstream>

void writeSchema(const Schema& schema, const std::string& path) {
    std::ofstream out(path, std::ios::binary);
    uint32_t n = schema.columns.size();
    out.write((char*)&n, sizeof(n));

    for (auto& c : schema.columns) {
        uint32_t len = c.name.size();
        out.write((char*)&len, sizeof(len));
        out.write(c.name.data(), len);

        uint32_t type = (uint32_t)c.type;
        out.write((char*)&type, sizeof(type));
        out.write((char*)&c.size, sizeof(c.size));
    }
}

Schema readSchema(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    Schema s;

    uint32_t n;
    in.read((char*)&n, sizeof(n));

    for (uint32_t i = 0; i < n; i++) {
        Column c;
        uint32_t len;
        in.read((char*)&len, sizeof(len));

        c.name.resize(len);
        in.read(c.name.data(), len);

        uint32_t type;
        in.read((char*)&type, sizeof(type));
        c.type = (ColumnType)type;

        in.read((char*)&c.size, sizeof(c.size));
        s.columns.push_back(c);
    }
    return s;
}
