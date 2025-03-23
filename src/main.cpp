/**
 * @file main.cpp
 * @author Miftahul (ecsolticia@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <SDL2/SDL.h>

#include <iostream>

#include "simulation/simulation_core.h"

int main() {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Grid grid = Grid(64, 64);

    StateManager state_manager = StateManager();
    state_manager.set_max_states(2);
    SDL_Color green;
    green.r = 0;
    green.g = 255;
    green.b = 0;
    green.a = 255;
    SDL_Color black;
    black.r = 0;
    black.g = 0;
    black.b = 0;
    black.a = 255;

    try {
        state_manager.add_state(black);
        state_manager.add_state(green);
    } catch (std::length_error le) {
        std::cerr << "Length error booh" << std::endl;
        return 0;
    }

    GridInterface grid_interface = GridInterface(window, renderer, &grid, &state_manager);
    grid_interface.set_cell_length(64);

    SimulationCore sim_core = SimulationCore(&grid_interface);

    std::function<size_t(size_t, size_t)> eval_func = [grid](size_t x, size_t y) -> size_t {
        return !grid.get_data(x, y);
    };

    sim_core.set_cell_eval(eval_func);

    grid_interface.create_window(512, 512);

    for (size_t i = 0; i < 10; ++i) {
        grid.set_data(i, i, 1);
    }

    //sim_core.execute_step();
    grid_interface.update_display_as_whole();

    SDL_Delay(5000);

    return 0;
}