#include "simulation_core.h"

void SimulationCore::set_cell_eval(std::function<size_t(size_t, size_t)> cell_eval) {
    this->cell_eval = cell_eval;
}

void SimulationCore::execute_step() const {
    if (this->cell_eval == nullptr) {
        throw std::bad_function_call();
    }

    Grid* grid = (this->grid_interface)->get_grid();
    
    const size_t max_i = grid->get_width();
    const size_t max_j = grid->get_height();

    // looping through the columns
    for (size_t i = 0; i < max_i; ++i) {
        // looping through each entry of the column
        for (size_t j = 0; j < max_j; ++j) {
            // calculate new value
            size_t new_val = (this->cell_eval(i, j));
            
            // set data accordingly
            grid->set_data(i, j, new_val);
        }
    }
}

SimulationCore::SimulationCore(GridInterface* grid_interface) {
    this->grid_interface = grid_interface;
}