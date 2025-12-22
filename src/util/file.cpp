#include "util/file.h"

File::File(const std::string& path, bool write) {
    if (write) {
        fs.open(path, std::ios::binary | std::ios::out | std::ios::app);
    } else {
        fs.open(path, std::ios::binary | std::ios::in);
    }
}

void File::write(const char* data, size_t size) {
    fs.write(data, size);
}

bool File::read(char* data, size_t size) {
    fs.read(data, size);
    return fs.gcount() == static_cast<std::streamsize>(size);
}

void File::close() {
    fs.close();
}
