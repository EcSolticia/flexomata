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
#include "configloader.h"

namespace FlexomataArguments {

    const std::string get_first_argument(const int argc, char** argv);

    void handle_file_existence(const std::string& path);

    const std::string get_valid_argument(const int argc, char** argv);

}

namespace FlexomataErrors {
    void handle_exception(const std::exception& e);
}

class SimulationScene {

    Grid grid;
    std::optional<Enforcer> enforcer;

public:
    const Grid* get_grid() const;
    const Enforcer* get_enforcer() const;

    void attach_rule(const FlexomataTypes::RuleFunc& rule);

    SimulationScene(const int argc, char** argv);

    SimulationScene(const std::string& config_text);
};