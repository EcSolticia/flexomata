#pragma once

#include <iostream> // For terminal I/O
#include <stdexcept> // For error-handling
#include <string>
#include <filesystem>
#include <memory>

#include "types.h"

#include "Grid/grid.h"
#include "Enforcer/enforcer.h"
#include "ConfigLoader/configloader.h"

namespace Arguments {

    const std::string get_first_argument(const int argc, char** argv);

    void handle_file_existence(const std::string& path);

    const std::string get_valid_argument(const int argc, char** argv);

}

namespace FlexomataErrors {
    void handle_exception(const std::exception& e);
}

class FlexomataInterface {

    std::unique_ptr<Grid> grid_ptr;
    std::unique_ptr<Enforcer> enforcer_ptr;

public:
    const Grid* get_grid() const;
    Enforcer* get_enforcer() const;

    void attach_rule(const FlexomataTypes::RuleFunc& rule);

    FlexomataInterface(const int argc, char** argv);
};