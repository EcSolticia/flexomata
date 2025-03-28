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
     * values are equal.
     * 
     * @param other The state to compare the present state to.
     * @return true If their values match.
     * @return false Otherwise.
     */
    bool operator==(const State& other) const {
        bool values_eq = (this->value == other.value);
        SDL_Color c1 = this->color;
        SDL_Color c2 = other.color;
        bool colors_eq = (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
        return (values_eq && colors_eq);
    }
    /**
     * @brief Negation of the comparison operator.
     * 
     * @param other The state to compare the present state to.
     * @return true If their values do not match. 
     * @return false Otherwise.
     */
    bool operator!=(const State& other) const {
        return (!(*this == other));
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
     * @brief Get the State defined at the specified index.
     * 
     * @pre That `sort_and_check` has already been called and it did not
     * throw errors. The `StateManager` constructor is expected to call
     * `sort_and_check` following value assignment, and it is expected that
     * the program will close prior to reaching this point if it throws an
     * error due to inconsistency.
     * 
     * @pre That the states vector is non-empty to avoid segmentation faults.
     * This is ensured by the constructor of the object itself, which would
     * throw an error if an attempt to initialize it with an empty vector is made.
     * 
     * @param of_value The value of the State to get.
     * @return State 
     */
    State get_state(const Uint8 of_value) const;

    /**
     * @brief Get the color of the state defined with the specified value.
     * 
     * @pre That `sort_and_check` has already been called and it did not
     * throw errors. The `StateManager` constructor is expected to call
     * `sort_and_check` following value assignment, and it is expected that
     * the program will close prior to reaching this point if it throws an
     * error due to inconsistency.
     * 
     * @pre That the states vector is non-empty to avoid segmentation faults.
     * This is ensured by the constructor of the object itself, which would
     * throw an error if an attempt to initialize it with an empty vector is made.
     * 
     * @note Is executed from within the simulation loop.
     * 
     * @param value The value of the state.
     * @return SDL_Color The color associated with the state.
     */
    SDL_Color get_color_of_state(const Uint8 value);

    /**
     * @brief Construct a new StateManager object
     * 
     * @throws std::domain_error If the passed states vector is empty.
     * @param states_p
     */
    StateManager(const std::vector<State>& states);

    /**
     * @brief Construct a new StateManager object. (Copy constructor)
     *
     * @note Does not perform sorting and checks as it is a copy.
     * 
     * @param from 
     */
    StateManager(const StateManager& from);
};
