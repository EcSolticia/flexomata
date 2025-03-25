#include "grid/statemanager.h"

int main() {
    SDL_Color col = SDL_Color();
    col.r = 0;
    col.g = 0;
    col.b = 0;
    col.a = 0;

    State s1;
    s1.value = 0;
    s1.color = col;

    State s2;
    s2.value = 1;
    s2.color = col;

    State s3;
    s3.value = 1;
    s3.color = col;

    std::vector<State> states;
    states.resize(3);
    states[0] = s1;
    states[1] = s2;
    states[2] = s3;
    StateManager sm = StateManager(states);

    sm.get_color_of_state(2);

    return 0;
}