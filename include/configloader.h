#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Flexomata {

class Grid;

class ConfigLoader {

    void load_grid_data(const std::string& stringset, Grid* grid_ptr) const;
    Grid initial_grid;

    Grid* target_grid_ptr = nullptr;

public:
    struct construct_from_path {};
    struct construct_from_text {};
    struct construct_for_later {};

    void load_into_target() const;
    void set_grid_config(const size_t x, const size_t y, const size_t value);
    ConfigLoader(const size_t width, const size_t height, Grid* grid_ptr, construct_for_later);

    ConfigLoader(const std::string& config_path, Grid* grid_ptr, construct_from_path);   
    ConfigLoader(const std::string& config_text, Grid* grid_ptr, construct_from_text);
};

}