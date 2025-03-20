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

#include "grid/grid.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    Grid g = Grid(1, 1);
    if (g.get_data(0, 0) == -1) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    return 0;
}