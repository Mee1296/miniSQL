#include <filesystem>

void createTableDir(const std::string& name) {
    std::filesystem::create_directories("data/" + name);
}
