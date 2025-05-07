#include "flexomata.h"

void FlexomataErrors::handle_exception(const std::exception& e) {
    if (typeid(e) == typeid(std::invalid_argument)) {
        std::cerr << "invalid_argument: " << e.what() << '\n';
    } else if (typeid(e) == typeid(std::domain_error)) {
        std::cerr << "domain_error: " << e.what() << '\n';
    } else if (typeid(e) == typeid(std::out_of_range)) {
        std::cerr << "out_of_range: " << e.what() << '\n';
    } else if (typeid(e) == typeid(std::logic_error)) {
        std::cerr << "logic_error: " << e.what() << '\n';
    } else if (typeid(e) == typeid(std::runtime_error)) {
        std::cerr << "runtime_error: " << e.what() << '\n';
    } else {
        std::cerr << "std::exception: " << e.what() << '\n';
    }
}

const std::string FlexomataArguments::get_first_argument(const int argc, char** argv) {
    std::string config_path;

        if (argc == 1) {
            config_path = "config.txt";
        }

        // assume argv[1] to be the configuration file path
        // currently ignores additional FlexomataArguments
        if (argc > 2) {
            std::cout << "Flexomata only accepts one command-line argument. The rest will be ignored.\n";
        }

        if (config_path.empty()) {
            config_path = argv[1];
        }

        return config_path;
}

void FlexomataArguments::handle_file_existence(const std::string& path) {
    bool exists = std::filesystem::exists(path);
    if (!exists) {
        throw std::runtime_error("No file exists at path " + path);
    }
}

const std::string FlexomataArguments::get_valid_argument(const int argc, char** argv) {
    const std::string config_path = get_first_argument(argc, argv);
    handle_file_existence(config_path);
    return config_path;
}

namespace Flexomata {

const Grid* SimulationScene::get_grid() const {
    return &this->grid;
}

const Enforcer* SimulationScene::get_enforcer() const {
    if (!this->enforcer.has_value()) {
        throw std::runtime_error("No rule attached to the simulation interface.");
    }
    return &this->enforcer.value();
}

DeferredConfigLoader* SimulationScene::get_deferred_configloader() {
    if (!this->deferred_configloader.has_value()) {
        throw std::runtime_error("To use the deferred configloader, construct the SimulationScene accordingly.");
    }
    return &this->deferred_configloader.value();
}

void SimulationScene::attach_rule(const FlexomataTypes::RuleFunc& rule) {
    this->enforcer = Enforcer(rule, &this->grid);
}

SimulationScene::SimulationScene(const int argc, char** argv) {
    this->grid = Grid();

    std::string config_path = FlexomataArguments::get_valid_argument(argc, argv);
    ConfigLoader configloader = ConfigLoader(config_path, &this->grid, ConfigLoader::construct_from_path{});
}

SimulationScene::SimulationScene(const std::string& config_text, construct_from_text) {
    this->grid = Grid();
    ConfigLoader configloader = ConfigLoader(config_text, &this->grid, ConfigLoader::construct_from_text{});
}

SimulationScene::SimulationScene(const std::string& config_path, construct_from_predefined_path) {
    this->grid = Grid();
    ConfigLoader configloader = ConfigLoader(config_path, &this->grid, ConfigLoader::construct_from_path{});
}

SimulationScene::SimulationScene(const size_t grid_width, const size_t grid_height, construct_from_deferred_config) {
    this->grid = Grid();
    this->deferred_configloader = DeferredConfigLoader(grid_width, grid_height, &this->grid);
}

}