#include "statemanager.h"

State StateManager::get_state(const Uint8 of_value) const {
    return (this->states)[of_value];
}

void StateManager::sort_and_check() {
    // sort
    auto comparison_func = [](const State& a, const State& b) { return a.value < b.value;};
    std::sort(this->states.begin(), this->states.end(), comparison_func);

    // check
    for (size_t i = 0; i < (this->states).size(); ++i) {
        if ((this->states)[i].value != i) {
            throw std::runtime_error("StateManager states variable is inconsistent.");
        }
    }
}

SDL_Color StateManager::get_color_of_state(const Uint8 value) {
    return states[value].color;
}

StateManager::StateManager(const std::vector<State>& states) {
    this->states = states;

    this->sort_and_check();

    if ((this->states).size() == 0) {
        throw std::domain_error("The `states` vector is found to be empty.");
    }
}

StateManager::StateManager(const StateManager& from) {
    this->states = from.states;
}