#include "grid.h"

void Grid::set_data(const std::vector<size_t>& dummy_data) {
    size_t size = this->height * this->width;

    if (dummy_data.size() < size) {
        throw std::runtime_error("Attempting to load the grid data vector with insufficient cell count.");
    }
    
    data.resize(size); // Not strictly necessary
    data.assign(dummy_data.begin(), dummy_data.begin() + size);
}

void Grid::set_pixel(const size_t x, const size_t y, const size_t value) {
    if (this->width <= x || this->height <= y) {
        throw std::out_of_range("Attempting to assign state value to a non-existent Grid coordinate.");
    }

    const size_t idx = this->width * y + x;

    this->data[idx] = value;
}

void Grid::initialize_grid(const size_t width, const size_t height) {

    this->width = width;
    this->height = height;

    this->data.resize(width * height);
    std::fill(this->data.begin(), this->data.end(), 0);
}

Grid::Grid() {
    this->width = 0;
    this->height = 0;
}