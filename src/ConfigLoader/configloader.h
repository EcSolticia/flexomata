#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../Grid/grid.h"

class ConfigLoader {

    void load_grid_data(const std::string& stringset, Grid* grid_ptr) const;

public:
    ConfigLoader(const std::string& config_path, Grid* grid_ptr);
};
