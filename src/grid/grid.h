/**
 * @file grid.h
 * @author Miftahul (ecsolticia@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <vector>

/**
 * @brief The structure representing the cellular automata grids
 * 
 * Represents the value at the ith column and jth row as `data[i][j]`.
 * Therefore, the elements in `data` are the columns.
 * 
 */
class Grid {
    size_t width;
    size_t height;
    std::vector<std::vector<int>> data;

public:
    ///  Enum for representing direction in the Grid object
    enum Direction {
        TOP_LEFT, /// Top left
        TOP, /// Top
        TOP_RIGHT, /// Top right
        LEFT, /// Left
        RIGHT, /// Right
        BOTTOM_LEFT, /// Bottom left
        BOTTOM, /// Bottom
        BOTTOM_RIGHT, /// Bottom right
    };

    void set_width(const size_t width) {
        this->width = width;
    }
    const size_t get_width() const {
        return this->width;
    }
    void set_height(const size_t height) {
        this->height = height;
    }
    const size_t get_height() const {
        return this->height;
    }

    /**
     * @brief Set a specific cell in the grid to a certain value
     * 
     * @param x The x coordinate of the cell to set.
     * @param y The y coordinate of the cell to set.
     * @param value The value to set the cell to.
     */
    void set_data(const size_t x, const size_t y, const int value);
    /**
     * @brief Get the value of a specific cell in the grid
     * 
     * @param x The x coordinate of the cell the value of which to get.
     * @param y The y coordinate of the cell the value of which to get.
     * @return int 
     */
    int get_data(const size_t x, const size_t y) const;
    /**
     * @brief Get a full-constant pointer to the data variable
     * 
     * @return const std::vector<std::vector<int>>* const 
     */
    const std::vector<std::vector<int>>* const get_data() const;
    /**
     * @brief Get a neighboring cell in a particular direction
     * 
     * @param x The x coordinate of the reference cell
     * @param y The y coordinate of the reference cell
     * @param dir The neighbor to get
     * @return int 
     */
    int get_neighbor(const size_t x, const size_t y, Direction dir) const;

    /**
     * @brief Initialize the data variable
     * 
     * Appropriately resize the `data` variable and set each entry to -1.
     */
    void initialize_data();

    /**
     * @brief Construct a new Grid object
     * 
     * @param width The number of columns of the grid.
     * @param height The number of rows of the grid.
     */
    Grid(const size_t width, const size_t height);
};