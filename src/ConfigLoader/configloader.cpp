#include "configloader.h"

ConfigLoader::ConfigLoader(const std::string& config_path) {
    std::ifstream config_file(config_path);

    std::string line;
    while (std::getline(config_file, line)) {
        std::cout << line << "\n";
    }
}