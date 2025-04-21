#pragma once
#include <functional>
#include <stdexcept>

class Grid;

typedef std::function<size_t(size_t, size_t)> RuleFunc;

class Enforcer {
    Grid* grid_ptr;
    RuleFunc rule;

public:

    void enforce_once() const;

    void enforce(size_t by_steps) const;

    Enforcer(const RuleFunc& rule, Grid* grid_ptr);
};