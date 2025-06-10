#pragma once

#include <iostream> // For terminal I/O
#include <stdexcept> // For error-handling
#include <string>
#include <filesystem>
#include <memory>
#include <optional>

#include "types.h"

#include "grid.h"
#include "enforcer.h"

namespace FlexomataArguments {

    const std::string get_first_argument(const int argc, char** argv);

    void handle_file_existence(const std::string& path);

    const std::string get_valid_argument(const int argc, char** argv);

}

namespace FlexomataErrors {
    void handle_exception(const std::exception& e);
}

namespace Flexomata {

class DeferredConfigLoader;

class SimulationScene {

    Grid grid;
    std::optional<Enforcer> enforcer;
    std::unique_ptr<DeferredConfigLoader> deferred_configloader;

public:
    const Grid* get_grid() const;
    const Enforcer* get_enforcer() const;
    DeferredConfigLoader* get_deferred_configloader();

    void attach_rule(const FlexomataTypes::RuleFunc& rule);

    SimulationScene(const int argc, char** argv);

    struct construct_from_text{};
    struct construct_from_predefined_path{};

    SimulationScene(const std::string& config_text, construct_from_text);
    SimulationScene(const std::string& config_path, construct_from_predefined_path);

    struct construct_from_deferred_config{};

    SimulationScene(const size_t grid_width, const size_t grid_height, construct_from_deferred_config);

    ~SimulationScene();
};

}