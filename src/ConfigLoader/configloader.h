#include <string>
#include <fstream>
#include <iostream>

#include "../Grid/grid.h"

class ConfigLoader {
    
public:
    ConfigLoader(const std::string& config_path, Grid* grid_ptr);
};
