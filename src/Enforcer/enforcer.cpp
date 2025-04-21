#include "enforcer.h"
#include "../Grid/grid.h"

void Enforcer::enforce_once() const {
    const size_t max_j = grid_ptr->get_height();
    const size_t max_i = grid_ptr->get_width();

    for (size_t j = 0; j < max_j; ++j) {
        for (size_t i = 0; i < max_i; ++i) {
            grid_ptr->set_pixel(i, j, rule(i, j));
        }
    }
}

void Enforcer::enforce(size_t by_steps) const {
    while (by_steps) {
        enforce_once();

        --by_steps;
    }
}

Enforcer::Enforcer(const RuleFunc& rule, Grid* grid_ptr) {
    if (!grid_ptr->is_initialized()) {
        throw std::runtime_error("An Enforcer object must be initialized with an already initialized Grid object.");
        /* Why?
        ** To avoid having checks each time the member functions requiring that
        ** the Grid object is initialized are called.
        */
    }

    this->grid_ptr = grid_ptr;
    this->rule = rule;
}