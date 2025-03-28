#include "simcore.h"

void SimCore::execute_step() const {
    // check if Grid is initialized.
    if (grid == nullptr) {
        throw std::runtime_error("Grid object not initialized");
    }
    // ...and, if Grid::state_manager is initialized
    if (!((this->grid)->is_state_manager())) {
        throw std::runtime_error("The associated StateManager object of the associated Grid object is not initialized.");
    }

    // By design, the rule function is expected to have been already defined and validated.
    // No need for further checks!

    // Copy Grid
    std::unique_ptr<Grid> grid_snapshot = std::make_unique<Grid>(*(this->grid).get());

    // Get the number of columns and rows
    size_t columns = (this->grid)->get_width();
    size_t rows = (this->grid)->get_height();

    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            // Calculate new value based on the snapshot
            Uint8 new_val = this->rule_func(i, j, grid_snapshot->get_state_at(i, j).value);
            
            // Get new state
            State state = grid->get_state_of_value(new_val);
            
            // Modify the original grid object.
            grid->set_state_at(i, j, state);
        }
    }
}

SimCore::SimCore(std::function<size_t(size_t, size_t, Uint8)>& rule_func) {
    this->rule_func = rule_func;
}