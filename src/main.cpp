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
    Grid grid_obj = Grid(64, 64);

    StateManager state_manager = StateManager();
    state_manager.set_max_states(2);
    SDL_Color live;
    live.r = 0;
    live.g = 255;
    live.b = 0;
    live.a = 255;
    SDL_Color dead;
    dead.r = 0;
    dead.g = 0;
    dead.b = 0;
    dead.a = 255;

    try {
        state_manager.add_state(dead);
        state_manager.add_state(live);
    } catch (std::length_error le) {
        std::cerr << "Length error booh" << std::endl;
        return 0;
    }

    GridInterface grid_interface = GridInterface(window, renderer, &grid_obj, &state_manager);
    Grid* grid = grid_interface.get_grid();

    grid_interface.set_cell_length(16);

    SimulationCore sim_core = SimulationCore(&grid_interface);

    // conway's game of life
    std::function<size_t(size_t, size_t)> eval_func = [grid](size_t x, size_t y) -> size_t {
        size_t c = grid->get_neighbor_of_state_count(x, y, 1);

        if (grid->get_data(x, y) == 1) {
            return (size_t)(c == 2 || c == 3);
        } else {
            return (size_t)(c == 3);
        }
    };

    sim_core.set_cell_eval(eval_func);

    grid_interface.create_window(512, 512);
    
    grid->set_data(2, 2, 1);
    grid->set_data(2, 3, 1);
    grid->set_data(3, 3, 1);
    grid->set_data(2, 4, 1);

    grid_interface.update_display_as_whole();
    SDL_Delay(1000);

    sim_core.execute_step();

    grid_interface.update_display_as_whole();

    SDL_Delay(1000);

    return 0;
}