/**
 * @file grid.h
 * @author Miftahul (ecsolticia@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <memory>
#include "statemanager.h"
#include "coordsystem.h"

/**
 * @brief The class representing the Cellular Automaton Grid.
 * 
 */
class Grid {
	/**
	 * @brief The smart pointer to the object responsible for managing the states
	 * and their properties.
	 * 
	 */
	std::unique_ptr<StateManager> state_manager;

    /**
     * @brief The row-major order indexed vector containing data about cell states.
     * 
     */
    std::vector<State> cells;

	size_t width = 0;
    size_t height = 0;

	size_t side_length = 0;
	
	/**
	 * @brief Convert matrix-index to row-major order index.
	 *
	 * The formula: \n
	 * \f$ i = x + yN \f$ \n
	 * where \f$i\f$ is the row-major order index, \f$x\f$ the column and
	 * \f$y\f$ the row index of the entry in the matrix, and \f$N\f$ is
	 * the number of columns of the matrix (`width`).
	 * 
	 * @pre `x < width && y < height`.
	 * 
	 * @throws std::domain_error if the precondition is not satisfied.
	 * @param x The column index.
	 * @param y The row index.
	 * @returns size_t The row-major order index.
	 */
	size_t mindex_to_index(const size_t x, const size_t y) const;

	/**
	 * @brief Initializes the `cells` vector to exhibit expected behavior.
	 *
	 * In this context, expected behavior refers to being row-major order
	 * indexed, having a size of `width * height`, with all entries being
	 * zero-opacity `State` structures with value 0.
	 * 
	 * @pre That neither `height` nor `width` is zero, which the Grid
	 * constructor(s) should handle.
	 */
	void initialize_cells();

	/**
	 * @brief The associated class object for handling the coordinte system
	 * 
	 */
	std::unique_ptr<CoordSystem> coord_system;

public:

	/**
	 * @brief Construct the associated StateManager object with the provided
	 * states.
	 * 
	 * Requires that `state_manager` contains `nullptr`, that is, that the object
	 * has not previously been constructed.
	 * 
	 * @throws std::runtime_error If a StateManager object was already constructed.
	 * @param states 
	 */
	void initialize_state_manager(const std::vector<State>&	 states);

	/**
	 * @brief Get the color of the given State object.
	 * 
	 * @pre That the input State is a valid one. That is, it is defined in the
	 * StateManager. This function does not explicitly check if the given state
	 * is valid.
	 * @param state 
	 * @returns SDL_Color
	 */
	SDL_Color get_color_of_state(const State state) const;

	/**
	 * @brief Set the cell at the specified matrix index to the specified
	 * state.
	 *
	 * Does not check for state validity since the `StateManager` object constructor
	 * should throw an error in the case of invalidity.
	 * 
	 * @param x The column index.
	 * @param y The row index.
	 * @param to The state to set said cell to.
	 */
	void set_state_at(const size_t x, const size_t y, State to);

	/**
	 * @brief Get the state of the cell at the specified matrix index.
	 *
	 * @param x The column index.
	 * @param y The row index.
	 * @returns State The state at the specified matrix index.
	 */
	State get_state_at(const size_t x, const size_t y) const;

	/**
	 * @brief Construct a new Grid object.
	 * 
	 * @throws std::domain_error if either the number of columns, rows or the
	 * given side length is zero.
	 * @param width The number of columns.
	 * @param height The number of rows.
	 * @param side_length The side length of the Grid cell squares.
	 */
	Grid(const size_t width, const size_t height, const size_t side_length);
};