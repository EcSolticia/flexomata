/**
 * @file statemanager.h
 * @author Miftahul (ecsolticia@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "SDL2/SDL.h"
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

/**
 * @brief The fundamental structure representing the state of a cell.
 * 
 */
struct State {
    /**
     * @brief The unsigned 8-bit integer uniquely assigned to the state.
     * 
     */
    Uint8 value;
    /**
     * @brief The color associated with the state. A cell with said state
     * will be drawn in this color.
     * 
     */
    SDL_Color color;

    /**
     * @brief Overload the comparison operator
     * 
     * Considers two `State` objects to be "equal" if and only if their
     * values are equal. Assumes that each state considered by the state
     * manager will be unique, and hence have a unique color.
     * 
     * @param other The state to compare the present state to.
     * @return true If their values match.
     * @return false Otherwise.
     */
    bool operator==(const State& other) const {
        return (this->value == other.value);
    }
};

/**
 * @brief Interface for defining and managing different states.
 * 
 * It sorts states in an ascending order and expects each unsigned integer from 0
 * to the the maximum state value to correspond to a defined state. If there is a
 * missing state, it throws an error.
 */
class StateManager {
    /**
     * @brief The vector of defined states.
     * 
     * Cannot be modified following initialization.
     * 
     */
    std::vector<State> states;

    /**
     * @brief Sorts the `states` variable in an ascending order and checks for consistency.
     *
     * The `StateManager` class expects each unsigned integer from 0 to the maximum state
     * value to be present. If a state is missing, an exception is thrown.
     *
     * @throws std::runtime_error If a state is missing from the sequence.
     */
    void sort_and_check();

public:

    /**
     * @brief Get the color of the state defined with the specified value.
     * 
     * Assumes that `sort_and_check` has already been called and it did not
     * throw errors. The `StateManager` constructor is expected to call
     * `sort_and_check` following value assignment, and it is expected that
     * the program will close prior to reaching this point if it throws an
     * error due to inconsistency.
     * 
     * Is executed from within the simulation loop.
     * 
     * To avoid segfaults, requires that the `states` vector is non-empty.
     * 
     * @param value The value of the state.
     * @return SDL_Color The color associated with the state.
     */
    SDL_Color get_color_of_state(const Uint8 value);

    /**
     * @brief Construct a new StateManager object
     * 
     * @param states_p
     */
    StateManager(const std::vector<State>& states);
};
