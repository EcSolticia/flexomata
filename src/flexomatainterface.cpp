#include "flexomatainterface.h"

const std::string Arguments::get_first_argument(const int argc, char** argv) {
    std::string config_path;

        if (argc == 1) {
            config_path = "config.txt";
        }

        // assume argv[1] to be the configuration file path
        // currently ignores additional arguments
        if (argc > 2) {
            std::cout << "Flexomata only accepts one command-line argument. The rest will be ignored.\n";
        }

        if (config_path.empty()) {
            config_path = argv[1];
        }

        return config_path;
}

void Arguments::handle_file_existence(const std::string& path) {
    bool exists = std::filesystem::exists(path);
    if (!exists) {
        const std::string message = "No file exists at path " + path;
        throw std::runtime_error(message);
    }
}

const std::string Arguments::get_valid_argument(const int argc, char** argv) {
    const std::string config_path = get_first_argument(argc, argv);
    handle_file_existence(config_path);
    return config_path;
}

const Grid* FlexomataInterface::get_grid() const {
    return this->grid_ptr.get();
}

Enforcer* FlexomataInterface::get_enforcer() const {
    if (!this->enforcer_ptr) {
        throw std::runtime_error("No rule attached to the simulation interface.");
    }
    return this->enforcer_ptr.get();
}

void FlexomataInterface::attach_rule(const FlexomataTypes::RuleFunc& rule) {
    this->enforcer_ptr = std::make_unique<Enforcer>(rule, this->grid_ptr.get());
}

FlexomataInterface::FlexomataInterface(const int argc, char** argv) {
    std::string config_path = Arguments::get_valid_argument(argc, argv);

    this->grid_ptr = std::make_unique<Grid>();

    ConfigLoader configloader = ConfigLoader(config_path, grid_ptr.get());
}