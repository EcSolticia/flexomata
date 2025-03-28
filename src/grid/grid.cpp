#include "grid.h"

size_t Grid::get_width() const {
    return this->width;
}
size_t Grid::get_height() const {
    return this->height;
}

size_t Grid::mindex_to_index(const size_t  x, const size_t y) const {
    // Check if the precondition is satisfied
    if (x >= this->width or y >= this->height) {
        throw std::domain_error("Matrix index out of bounds");
    }

    return (x + y * width);
}

SDL_Color Grid::get_color_of_state(const State state) const {
    // it is assumed that state_manager is initialized
    StateManager* sm = (this->state_manager).get();

    // check if the given state exists
    if (sm->get_state(state.value) != state) {
        throw std::domain_error("Given state not found");
    }

    return sm->get_color_of_state(state.value);
}

void Grid::set_state_at(const size_t x, const size_t y, State to) {
    CoordSystem* cs = (this->coord_system).get();

    // Calculate valid matrix indices
    const size_t m_x = cs->get_component(x, cs->PERIODIC, cs->X);
    const size_t m_y = cs->get_component(y, cs->PERIODIC, cs->Y);

    // Convert matrix index to linear index
    const size_t i = this->mindex_to_index(m_x, m_y);

    // Set data
    this->cells[i] = to;
}

State Grid::get_state_at(const size_t x, const size_t y) const {
    CoordSystem* cs = (this->coord_system).get();

    // Calculate valid matrix indices
    const size_t m_x = cs->get_component(x, cs->PERIODIC, cs->X);
    const size_t m_y = cs->get_component(y, cs->PERIODIC, cs->Y);

    // Convert matrix index to linear index
    const size_t i = this->mindex_to_index(m_x, m_y);

    return this->cells[i];
}

void Grid::initialize_cells() {
    // There's no need to check for precondition satisfaction here since
    // the constructor is expected to throw an error in the case that it is 
    // not satisfied

    // Create the placeholder state
    State zero;
    zero.value = 0;
    SDL_Color zero_col;
    zero_col.r = 0;
    zero_col.g = 0;
    zero_col.b = 0;
    zero_col.a = 0;
    zero.color = zero_col;

    size_t cells_count = this->height * this->width;

    // ensure appropriate size
    (this->cells).resize(cells_count);
    
    // assign default state
    std::fill((this->cells).begin(), (this->cells).end(), zero);
}

void Grid::initialize_state_manager(const std::vector<State>& states) {
    // Check if the states_manager has previously been initialized
    if (this->is_state_manager()) {
        throw std::runtime_error("A StateManager object has already been constructed");
    }

    // Construct and assign the StateManager object
    this->state_manager = std::make_unique<StateManager>(states);
}

bool Grid::is_state_manager() const {
    return ((this->state_manager).get() != nullptr);
}

State Grid::get_state_of_value(const Uint8 value) const {
    return (this->state_manager)->get_state(value);
}

Grid::Grid(const size_t width, const size_t height, const size_t side_length) {
    // check for zero-dimensionality
    if (width == 0 || height == 0 || side_length == 0) {
        throw std::domain_error("Input parameter to the Grid constructor cannot be zero");
    }

    // Set appropriate values
    this->width = width;
    this->height = height;
    this->side_length = side_length;
    this->coord_system = std::make_unique<CoordSystem>(this->width, this->height);
}

Grid::Grid(const Grid& from) {
    this->width = from.width;
    this->height = from.height;
    this->side_length = from.side_length;
    this->coord_system = std::make_unique<CoordSystem>(*(from.coord_system).get());
    this->state_manager = std::make_unique<StateManager>(*(from.state_manager).get());

    this->cells = from.cells;
}