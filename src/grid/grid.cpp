#include "grid.h"

void Grid::set_data(const size_t x, const size_t y, const size_t value) {
    this->data[(x + this->get_width()) % this->get_width()][(y + this->get_height()) % this->get_height()] = value;
}
size_t Grid::get_data(const size_t x, const size_t y) const {
    return this->data[(x + this->get_width()) % this->get_width()][(y + this->get_height()) % this->get_height()];
}

size_t Grid::get_neighbor(const size_t x, const size_t y, Direction dir) const {
    size_t tl_x;
    size_t tl_y;
    switch(dir) {
        case TOP_LEFT:
            tl_x = (x - 1 + this->get_width()) % this->get_width();
            tl_y = (y - 1 + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case TOP:
            tl_x = (x + this->get_width()) % this->get_width();
            tl_y = (y - 1 + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case TOP_RIGHT:
            tl_x = (x + 1 + this->get_width()) % this->get_width();
            tl_y = (y - 1 + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case LEFT:
            tl_x = (x - 1 + this->get_width()) % this->get_width();
            tl_y = (y + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case RIGHT:
            tl_x = (x + 1 + this->get_width()) % this->get_width();
            tl_y = (y + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case BOTTOM_LEFT:
            tl_x = (x - 1 + this->get_width()) % this->get_width();
            tl_y = (y + 1 + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case BOTTOM:
            tl_x = (x + this->get_width()) % this->get_width();
            tl_y = (y + 1 + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
        case BOTTOM_RIGHT:
            tl_x = (x + 1 + this->get_width()) % this->get_width();
            tl_y = (y + 1 + this->get_height()) % this->get_height();
            return this->get_data(tl_x, tl_y);
            break;
    }
    return -1;
}

size_t Grid::get_neighbor_of_state_count(const size_t x, const size_t y, const size_t state) const {
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
        std::vector<size_t> new_column;
        // Number of rows = height
        new_column.resize(height);

        // Assign default value to row entries
        for (size_t j = 0; j < height; ++j) {
            new_column[j] = 0;
        }

        this->data[i] = new_column;
    }
    
}
Grid::Grid(const size_t width, const size_t height) {
    this->set_width(width);
    this->set_height(height);

    initialize_data();
}



void GridInterface::create_window(const size_t width, const size_t height) {
    SDL_CreateWindowAndRenderer(width, height, 0, &(this->window), &(this->renderer));

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);
}

Vector2 GridInterface::get_rect_origin(const size_t x, const size_t y) const {
    Vector2 result;
    result.resize(2);
    size_t side_length = this->get_cell_length();
    result[0] = this->get_pivot_x() + x * side_length;
    result[1] = this->get_pivot_y() + y * side_length;
    return result;
}

void GridInterface::draw_cell(const size_t x, const size_t y, const size_t state) const {
    Vector2 org = this->get_rect_origin(x, y);

    SDL_Rect rect;
    rect.x = org[0];
    rect.y = org[1];
    rect.w = this->get_cell_length();
    rect.h = this->get_cell_length();

    SDL_Color color = (this->state_manager)->get_state_color(state);
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->renderer, &rect);
}

void GridInterface::update_display_as_whole() {
    // clear display first
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);

    size_t grid_w = (this->get_grid())->get_width();
    size_t grid_h = (this->get_grid())->get_height();

    // loop through the columns
    for (size_t i = 0; i < grid_w; ++i) {
        // loop through rows
        for (size_t j = 0; j < grid_h; ++j) {
            size_t state_here = (this->grid)->get_data(i, j);
            this->draw_cell(i, j, state_here);
        }
    }

    // Only present after the entire visual update is done
    SDL_RenderPresent(this->renderer);
};

void GridInterface::present_display(const size_t delay) const {
    SDL_RenderPresent(this->renderer);
    SDL_Delay(delay);
}

GridInterface::GridInterface(SDL_Window* window, SDL_Renderer* renderer, Grid* grid, StateManager* state_manager) {
    this->window = window;
    this->renderer = renderer;
    this->grid = grid;
    this->state_manager = state_manager;

    this->set_cell_length(8);
    this->set_pivot(0, 0);
}