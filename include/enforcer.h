#pragma once
#include <functional>
#include <stdexcept>

#include "types.h"

class Grid;

class Enforcer {

    Grid* grid_ptr;
    FlexomataTypes::RuleFunc rule;

public:

    void enforce_once() const;

    void enforce(size_t by_steps) const;

    Enforcer(const FlexomataTypes::RuleFunc& rule, Grid* grid_ptr);
};