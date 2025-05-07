#pragma once

namespace Flexomata {

class Grid;

class DeferredConfigLoader {
    Grid intermediary_grid;
    Grid* target_grid_ptr;

public:

    void load_config_into_target() const;

    void set_config_pixel(const size_t x, const size_t y, const size_t value);

    DeferredConfigLoader(const size_t width, const size_t height, Grid* target_grid_ptr);
};

}