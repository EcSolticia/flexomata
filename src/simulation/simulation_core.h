/**
 * @file simulation_core.h
 * @author Miftahul (ecsolticia@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../grid/grid.h"
#include <functional>

/**
 * @brief The core class for handling the simulation
 * 
 */
class SimulationCore {
    GridInterface* grid_interface = nullptr;
    
    std::function<size_t(size_t, size_t)> cell_eval = nullptr;

public:
    void set_cell_eval(std::function<size_t(size_t, size_t)> cell_eval);

    /**
     * @brief Execute the simulation rules and apply the next step
     * 
     * Updates display after done
     * 
     * Doesn't affect other member variables
     */
    void execute_step() const;

    SimulationCore(GridInterface* grid_interface);
};