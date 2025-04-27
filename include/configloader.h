#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Grid;

class ConfigLoader {

    void load_grid_data(const std::string& stringset, Grid* grid_ptr) const;

public:
    struct construct_from_path {};
    struct construct_from_text {};

    ConfigLoader(const std::string& config_path, Grid* grid_ptr, construct_from_path);   
    ConfigLoader(const std::string& config_text, Grid* grid_ptr, construct_from_text);
};
