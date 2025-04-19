#include "grid.h"

bool Grid::are_init_vars(const size_t width, const size_t height, const size_t max_state) const {
    return (this->width && this->height && this->max_state);
}

void Grid::set_pixel(const size_t x, const size_t y, const size_t value) {
    if (this->width <= x || this->height <= y) {
        throw std::out_of_range("Attempting to assign state value to a non-existent Grid coordinate.");
    }

    const size_t idx = this->width * y + x;

    if (value > max_state) {
        throw std::domain_error("Given state value does not exist.");
    }

    this->data[idx] = value;
}

void Grid::initialize_grid(const size_t width, const size_t height, const size_t max_state) {

    this->width = width;
    this->height = height;
    this->max_state = max_state;

    this->data.resize(width * height);
    std::fill(this->data.begin(), this->data.end(), 0);
}

Grid::Grid() {
    this->width = 0;
    this->height = 0;
    this->max_state = 0;
}