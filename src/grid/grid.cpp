#include "grid.h"

void Grid::set_data(const size_t x, const size_t y, const int value) {
    this->data[x % this->get_width()][y % this->get_height()] = value;
}
int Grid::get_data(const size_t x, const size_t y) const {
    return this->data[x][y];
}
const std::vector<std::vector<int>>* const Grid::get_data() const {
    return &(this->data);
}

int Grid::get_neighbor(const size_t x, const size_t y, Direction dir) const {
    size_t tl_x;
    size_t tl_y;
    switch(dir) {
        case TOP_LEFT:
            tl_x = (x - 1) % this->get_width();
            tl_y = (y - 1) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case TOP:
            tl_x = x % this->get_width();
            tl_y = (y - 1) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case TOP_RIGHT:
            tl_x = (x + 1) % this->get_width();
            tl_y = (y - 1) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case LEFT:
            tl_x = (x - 1) % this->get_width();
            tl_y = y % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case RIGHT:
            tl_x = (x + 1) % this->get_width();
            tl_y = y % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case BOTTOM_LEFT:
            tl_x = (x - 1) % this->get_width();
            tl_y = (y + 1) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case BOTTOM:
            tl_x = x % this->get_width();
            tl_y = (y + 1) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case BOTTOM_RIGHT:
            tl_x = (x + 1) % this->get_width();
            tl_y = (y + 1) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
    }
    return -1;
}

size_t Grid::get_neighbor_of_state_count(const size_t x, const size_t y, int state) const {
    size_t count = 0;
    for (size_t i = 0; i < 8; ++i) {
        if (get_neighbor(x, y, static_cast<Direction>(i)) == state) {
            ++count;
        }
    }
    return count;
}

void Grid::initialize_data() {
    const size_t width = this->get_width();
    const size_t height = this->get_height();

    // Number of columns = width
    this->data.resize(width);

    for (size_t i = 0; i < width; ++i) {
        std::vector<int> new_column;
        // Number of rows = height
        new_column.resize(height);

        // Assign default value to row entries
        for (size_t j = 0; j < height; ++j) {
            new_column[j] = -1;
        }

        this->data[i] = new_column;
    }
    
}
Grid::Grid(const size_t width, const size_t height) {
    this->set_width(width);
    this->set_height(height);

    initialize_data();
}

void GridDisplay::create_window_with_bg(const size_t width,
                                        const size_t height, 
                                        const size_t r, 
                                        const size_t g, 
                                        const size_t b, 
                                        const size_t a) 
{

    SDL_CreateWindowAndRenderer(width, height, 0, &(this->window), &(this->renderer));

    SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
    SDL_RenderClear(this->renderer);
}

Vector2 GridDisplay::get_rect_origin(const size_t x, const size_t y) const {
    Vector2 result;
    result.resize(2);
    size_t side_length = this->get_cell_length();
    result[0] = this->get_pivot_x() + x * side_length;
    result[1] = this->get_pivot_y() + y * side_length;
    return result;
}

void GridDisplay::draw_cell(const size_t x, const size_t y) const {
    Vector2 org = this->get_rect_origin(x, y);

    SDL_Rect rect;
    rect.x = org[0];
    rect.y = org[1];
    rect.w = this->get_cell_length();
    rect.h = this->get_cell_length();

    /*
    if (grid->get_data(x, y) == 1) {
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 1);
        SDL_RenderDrawRect(this->renderer, &rect);
    } else {
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(this->renderer, &rect);
    }
    */
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 1);
    SDL_RenderDrawRect(this->renderer, &rect);
}

void GridDisplay::present_display(const size_t delay) {
    SDL_RenderPresent(this->renderer);
    SDL_Delay(delay);
}

GridDisplay::GridDisplay(SDL_Window* window, SDL_Renderer* renderer, Grid* grid) {
    this->window = window;
    this->renderer = renderer;
    this->grid = grid;

    this->set_cell_length(8);
    this->set_pivot(0, 0);
}