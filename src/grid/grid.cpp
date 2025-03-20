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