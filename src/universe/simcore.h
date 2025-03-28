#pragma once

#include <memory>
#include <functional>

#include "../grid/grid.h"

/**
 * @brief Class for handling simulation rules, execution and rendering.
 * 
 */
class SimCore {
    /**
     * @brief The function that determines how each cell will evolve.
     * 
     * May also be called the "rule function".
     * 
     */
    std::function<size_t(size_t, size_t, Uint8)> rule_func = nullptr;

    /**
     * @brief The Grid object associated with the present SimCore object.
     * 
     */
    std::unique_ptr<Grid> grid = nullptr;
    
public:
    /**
     * @brief Initialize the associated Grid object.
     * 
     * @note Is a wrapper around `Grid::Grid(const size_t width, const size_t height,
     * const size_t side_length)`. Does not throw exceptions by itself, since the 
     * Grid constructor handles them already.
     * 
     * @throws std::runtime_error If the Grid object was already constructed.
     * @param width The number of columns of the Grid.
     * @param height The number of rows of the Grid.
     * @param side_length The side length of each cell.
     */
    void initialize_grid(const size_t width, const size_t height, const size_t side_length);
    
    /**
     * @brief Initialize the associated Grid object's StateManager.
     * 
     * @note Is a wrapper around `Grid::initialize_state_manager(const std::vector<State>& states)`
     * , which itself is a wrapper around
     * `StateManager::StateManager(const std::vector<State>& states)`.
     * 
     * @note Does not throw errors directly since the key function it is a wrapper around
     * already does so.
     * 
     * @param states 
     */
    void initialize_state_manager(const std::vector<State>& states);

    /**
     * @brief Check whether the StateManager object associated with the associated Grid
     * object is initialized.
     * 
     * @return true If initialized.
     * @return false Otherwise.
     */
    bool is_state_manager() const;

    /**
     * @brief Evaluates the subsequent State of each cell in the associated grid,
     * modifies the grid accordingly, and draws the changes to the screen.
     *
     * @throws std::runtime_error If the associated StateManager of the associated
     * Grid is not initialized.
     * @throws std::runtime_error If Grid is not initialized.
     */
    void execute_step() const;

    /**
     * @brief Construct a new SimCore object with the specified rule function.
     * 
     * @throws std::domain_error If the input parameter is `nullptr`.
     * @param rule_func 
     */
    SimCore(std::function<size_t(size_t, size_t, Uint8)>& rule_func);
};