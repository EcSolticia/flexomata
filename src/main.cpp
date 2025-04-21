#include <iostream> // For terminal I/O
#include <stdexcept> // For error-handling
#include <string>
#include <filesystem>
#include <memory>

#include "Grid/grid.h"
#include "ConfigLoader/configloader.h"
#include "Enforcer/enforcer.h"

namespace Arguments {

    const std::string get_first_argument(const int argc, char** argv) {
        std::string config_path;

        if (argc == 1) {
            //throw std::invalid_argument("Expected a command-line argument.");
            config_path = "config.txt";
        }

        // assume argv[1] to be the configuration file path
        // current ignore additional arguments
        if (argc > 2) {
            std::cout << "Flexomata only accepts one command-line argument. The rest will be ignored.\n";
        }

        if (config_path.empty()) {
            config_path = argv[1];
        }

        return config_path;
    }

    void handle_file_existence(const std::string& path) {
        bool exists = std::filesystem::exists(path);
        if (!exists) {
            const std::string message = "No file exists at path " + path;
            throw std::runtime_error(message);
        }
    }

    const std::string get_valid_argument(const int argc, char** argv) {
        const std::string config_path = get_first_argument(argc, argv);
        handle_file_existence(config_path);
        return config_path;
    }

}

int main(int argc, char** argv) {


    try {

    } catch (std::invalid_argument e) {
        std::cerr << "invalid_argument: " << e.what();
    } catch (std::runtime_error e) {
        std::cerr << "runtime_error: " << e.what();
    } catch (std::domain_error e) {
        std::cerr << "domain_error: " << e.what();
    } catch (std::out_of_range e) {
        std::cerr << "out_of_range: " << e.what();
    } catch (std::logic_error e) {
        std::cerr << "logic_error: " << e.what();
    } catch (std::exception e) {
        std::cerr << "An unexpected error occured.";
    } catch (...) {
        std::cerr << "An unkown error occured.";
    }

    //std::cerr << std::endl;
    std::cout << std::endl;

    return 0;
}
