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
        throw std::runtime_error("No file exists at path " + path);
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

const Enforcer* FlexomataInterface::get_enforcer() const {
    if (!this->enforcer_ptr) {
        throw std::runtime_error("No rule attached to the simulation interface.");
    }
    return this->enforcer_ptr.get();
}

void FlexomataInterface::attach_rule(const FlexomataTypes::RuleFunc& rule) {
    this->enforcer_ptr = std::make_unique<Enforcer>(rule, this->grid_ptr.get());
}

FlexomataInterface::FlexomataInterface(const int argc, char** argv) {
    this->grid_ptr = std::make_unique<Grid>();

    std::string config_path = Arguments::get_valid_argument(argc, argv);
    ConfigLoader configloader = ConfigLoader(config_path, grid_ptr.get(), ConfigLoader::construct_from_path{});
}
FlexomataInterface::FlexomataInterface(const std::string& config_text) {
    this->grid_ptr = std::make_unique<Grid>();
    ConfigLoader configloader = ConfigLoader(config_text, grid_ptr.get(), ConfigLoader::construct_from_text{});
}