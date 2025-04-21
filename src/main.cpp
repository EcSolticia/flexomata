#include "flexomatainterface.h"

int main(int argc, char** argv) {

    try {

        FlexomataInterface sim = FlexomataInterface(argc, argv);
        
        const Grid* grid_ptr = sim.get_grid();

        FlexomataTypes::RuleFunc game_of_life = [grid_ptr](const size_t x, const size_t y) -> size_t {
            const size_t neighbor_count = grid_ptr->get_neighbor_count(x, y, 1);
            const size_t alive = grid_ptr->get_pixel(x, y);

            if (alive) {
                return (neighbor_count == 2 || neighbor_count == 3);
            } else {
                return (neighbor_count == 3);
            }
        };

        sim.attach_rule(game_of_life);
        
        Enforcer* enforcer_ptr = sim.get_enforcer();

        enforcer_ptr->enforce_once();

        grid_ptr->print_data();

    } catch (const std::exception& e) {
        FlexomataErrors::handle_exception(e);
    }

    return 0;
}
