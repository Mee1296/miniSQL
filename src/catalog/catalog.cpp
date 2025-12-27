#include "catalog/catalog.h"
#include <fstream>
#include <algorithm>

static const std::string CATALOG_PATH = "data/catalog.meta";

static std::vector<std::string> readCatalog() {
   std::ifstream in(CATALOG_PATH, std::ios::binary);
    if (!in) return {};

    in.seekg(0, std::ios::end);
    if (in.tellg() < sizeof(uint32_t))
        return {};

    in.seekg(0);

    uint32_t n;
    in.read((char*)&n, sizeof(n));

    if (n > 1000) return {};

    std::vector<std::string> tables;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t len;
        if (!in.read((char*)&len, sizeof(len))) break;
        if (len > 256) break;  // sanity limit

        std::string name(len, '\0');
        if (!in.read(name.data(), len)) break;
        tables.push_back(name);
    }
    return tables;
}

static void writeCatalog(const std::vector<std::string>& tables) {
    std::ofstream out(CATALOG_PATH, std::ios::binary | std::ios::trunc);
    uint32_t n = tables.size();
    out.write((char*)&n, sizeof(n));

    for (auto& t : tables) {
        uint32_t len = t.size();
        out.write((char*)&len, sizeof(len));
        out.write(t.data(), len);
    }
}

void catalogAddTable(const std::string& table) {
    auto tables = readCatalog();
    if (std::find(tables.begin(), tables.end(), table) != tables.end())
        return;

    tables.push_back(table);
    writeCatalog(tables);
}

bool catalogRemoveTable(const std::string& table) {
    auto tables = readCatalog();
    auto old_size = tables.size();

    tables.erase(
        std::remove(tables.begin(), tables.end(), table),
        tables.end()
    );

    if (tables.size() == old_size)
        return false;

    writeCatalog(tables);
    return true;
}


std::vector<std::string> catalogListTables() {
    return readCatalog();
}

bool catalogExists(const std::string& table) {
    auto tables = readCatalog();
    return std::find(tables.begin(), tables.end(), table) != tables.end();
}
