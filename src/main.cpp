#include <iostream> // For terminal I/O
#include <stdexcept> // For error-handling
#include <string>
#include <filesystem>

#include "ConfigLoader/configloader.h"

namespace Arguments {

    std::string validate_arguments(const int argc, char** argv) {
        if (argc == 1) {
            throw std::invalid_argument("Expected a command-line argument.");
        }

        // assume argv[1] to be the configuration file path
        // current ignore additional arguments
        if (argc != 2) {
            std::cout << "Flexomata only accepts one command-line argument. The rest will be ignored.\n";
        }

        std::string config_path = argv[1];

        return config_path;
    }

    void handle_file_existence(const std::string& path) {
        bool exists = std::filesystem::exists(path);
        if (!exists) {
            const std::string message = "No file exists at path " + path;
            throw std::runtime_error(message);
        }
    }

}

int main(int argc, char** argv) {


    try {

        const std::string config_path = Arguments::validate_arguments(argc, argv);
        Arguments::handle_file_existence(config_path);

        ConfigLoader configloader = ConfigLoader(config_path);

        std::cout << std::endl;

    } catch (std::invalid_argument e) {
        std::cerr << "invalid_argument: " << e.what() << std::endl;
    } catch (std::runtime_error e) {
        std::cerr << "runtime_error: " << e.what() << std::endl;
    } catch (std::exception e) {
        std::cerr << "An unexpected error occured." << std::endl;
    } catch (...) {
        std::cerr << "An unkown error occured." << std::endl;
    }

    return 0;
}