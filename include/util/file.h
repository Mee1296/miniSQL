#pragma once
#include <fstream>
#include <string>

class File {
public:
    explicit File(const std::string& path, bool write);

    void write(const char* data, size_t size);
    bool read(char* data, size_t size);

    void close();

private:
    std::fstream fs;
};
