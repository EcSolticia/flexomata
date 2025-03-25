#pragma once

#include "SDL2/SDL.h"
#include <memory>

/**
 * @brief The fundamental structure representing a state of a cell.
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
};