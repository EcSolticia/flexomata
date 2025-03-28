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
#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <stdexcept>

#include <vector>

typedef std::vector<size_t> Vector2;

/**
 * @brief The structure representing the cellular automata grids
 * 
 * Represents the value at the ith column and jth row as `data[i][j]`.
 * Therefore, the elements in `data` are the columns.
 * 
 * Entries of the `data` variable are unsigned integers corresponding to states.
 * 
 * Bottom-level entries of the `data` variable represent the states of the cells.
 * 
 */
class Grid {
    size_t width;
    size_t height;
    std::vector<std::vector<size_t>> data;

public:
    ///  Enum for representing direction in the Grid object
    enum Direction {
        TOP_LEFT = 0, /// Top left
        TOP = 1, /// Top
        TOP_RIGHT = 2, /// Top right
        LEFT = 3, /// Left
        RIGHT = 4, /// Right
        BOTTOM_LEFT = 5, /// Bottom left
        BOTTOM = 6, /// Bottom
        BOTTOM_RIGHT = 7, /// Bottom right
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
    void set_data(const size_t x, const size_t y, const size_t value);
    /**
     * @brief Get the value of a specific cell in the grid
     * 
     * @param x The x coordinate of the cell the value of which to get.
     * @param y The y coordinate of the cell the value of which to get.
     * @return size_t 
     */
    size_t get_data(const size_t x, const size_t y) const;

    /**
     * @brief Get a neighboring cell in a particular direction
     * 
     * @param x The x coordinate of the reference cell
     * @param y The y coordinate of the reference cell
     * @param dir The neighbor to get
     * @return size_t 
     */
    size_t get_neighbor(const size_t x, const size_t y, Direction dir) const;

    /**
     * @brief Get the number of neighbors of a specified state
     * 
     * @param x The x coordinate of the reference cell
     * @param y The y coordinate of the reference cell
     * @param state The state to compare the neighbor to
     * @return size_t 
     */
    size_t get_neighbor_of_state_count(const size_t x, const size_t y, const size_t state) const;

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

    /**
     * @brief Construct a new Grid object (copy constructor)
     * 
     * @param grid The grid object to copy
     */
    Grid(const Grid& grid);

    ~Grid() {
    }
};

/**
 * @brief The class for managing different potential states of cells and their properties.
 * 
 * Each index of the member variable `color` corresponds to a state. Therefore, if `i` is a `size_t` representing
 * a state defined in this class, `color[i]` is the color corresponding to that state. That state will be drawn using
 * said color.
 * 
 */
class StateManager {
    /**
     * @brief Variable for keeping track of the number of defined states
     * 
     */
    size_t states;

    std::vector<SDL_Color> colors;

public:

    /**
     * @brief Set the number of states to be defined.
     * 
     * @param max_states 
     */
    void set_max_states(const size_t max_states) {
        (this->colors).resize(max_states);
    }

    /**
     * @brief 
     * 
     * @param color 
     */
    void add_state(SDL_Color color) {
        const size_t l = (this->colors).size();
        if (l < (this->states + 1)) {
            throw std::length_error("Attempting to add more states that maximum");
        }

        (this->colors)[states] = color;

        ++(this->states);
    }

    SDL_Color get_state_color(const size_t state) {
        if (state >= this->states) {
            throw std::length_error("Provided state value exceeds maximal state count");
        }

        return (this->colors)[state];
    }

    /**
     * @brief Construct a new StateManager object
     * 
     */
    StateManager() {
        this->states = 0;
        this->colors = std::vector<SDL_Color> ();
    }
};

/**
 * @brief Class for drawing the Grid on the window with SDL2
 * 
 */
class GridInterface {
    /**
     * @brief The height and width of each specific cell in pixels
     * 
     */
    size_t cell_length;
    /**
     * @brief The x coordinate of the pivot w.r.t. the window
     * 
     */
    size_t pivot_x;
    /**
     * @brief The y coordinate of the pivot w.r.t. the window
     * 
     */
    size_t pivot_y;

    SDL_Window* window;
    SDL_Renderer* renderer;
    Grid* grid;
    StateManager* state_manager;

public:
    void set_grid(Grid* grid) {
        delete this->grid;
        this->grid = grid;
    }

    void set_cell_length(const size_t cell_length) {
        this->cell_length = cell_length;
    }
    const size_t get_cell_length() const {
        return this->cell_length;
    }
    
    void set_pivot(size_t x, size_t y) {
        this->pivot_x = x;
        this->pivot_y = y;
    }
    size_t get_pivot_x() const {
        return this->pivot_x;
    }
    size_t get_pivot_y() const {
        return this->pivot_y;
    }

    Grid* get_grid() const {
        return this->grid;
    }

    /**
     * @brief Create the SDL Window and Renderer with a white background
     * 
     * @param width The width of the window
     * @param height The height of the window
     */
    void create_window(const size_t width, const size_t height);

    /**
     * @brief Get the top-left origin of the specified cell in the window
     * 
     * Represent the current function as \f$ f: \mathbb{N}^2 \rightarrow \mathbb{N}^2 \f$. \n 
     * 
     * We have \f$ f(0, 0) = (\text{pivot}_x, \text{pivot}_y) \f$. \n 
     * 
     * We want \f$ f(x + 1, y) = f(x, y) + (\text{cell_length}, 0) \f$,
     * and similarly, \f$ f(x, y + 1) = f(x, y) + (0, \text{cell_length}) \f$. \n
     * 
     * Consequently, \f$ f(x + i, y + j) = f(x, y) + \text{cell_length} * (i, j) \f$. \n
     * Therefore, \f$ f(x, y) = f(0, 0) + f(x, 0) + f(0, y) = (\text{pivot}_x, \text{pivot}_y)
     * + x * f(1, 0) + y * f(0, 1) \f$ \n
     * \f$ = (\text{pivot}_x, \text{pivot}_y) + \text{cell_length} * (x, y) \f$
     * 
     * \f$ f(x, y) = (\text{pivot}_x, \text{pivot}_y) + \text{cell_length} * (x, y) \f$
     * 
     * @param x The x coordinate of the cell
     * @param y The y coordinate of the cell
     * @return Vector2 
     */
    Vector2 get_rect_origin(const size_t x, const size_t y) const;

    /**
     * @brief Draw the cell with the given coordinate
     * 
     * @param x The x coordinate of the cell
     * @param y The y coordinate of the cell
     */
    void draw_cell(const size_t x, const size_t y, const size_t state) const;

    /**
     * @brief Iterates through each cell to draw the corresponding cell based on data
     * 
     */
    void update_display_as_whole();

    /**
     * @brief Present the renderer
     * 
     * @param delay Milliseconds taken till the program automatically terminates
     */
    void present_display(const size_t delay) const;

    GridInterface(SDL_Window* window, SDL_Renderer* renderer, Grid* grid, StateManager* state_manager);
    ~GridInterface();
};