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

#include "grid/grid.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Grid grid = Grid(16, 16);

    GridDisplay grid_display = GridDisplay(window, renderer, &grid);
    grid_display.create_window_with_bg(640, 480, 255, 255, 255, 255);
    grid_display.draw_cell(8, 8);
    grid_display.draw_cell(9, 8);
    grid_display.draw_cell(10, 8);
    grid_display.draw_cell(12, 12);
    grid_display.present_display(5000);

    return 0;
}