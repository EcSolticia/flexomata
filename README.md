# Flexomata

Flexomata is a simple framework for handling cellular automata simulation in C++ as a static library. The user may provide a "rule function" to operate per each grid cell along with an initial configuration. Flexomata can thereafter apply the rule to each cell and offers access to the evolved state of the grid.

# Usage Documentation
## Accessible Classes and Namespaces
### `FlexomataInterface` (`flexomata.h`)
Creates a separate "universe" for a particular simulation, with predefined Grid dimensions and an initial configuration. Is the entry point for all pertinent simulation functionalities. Other accessible classes can only be accessed through an instance of `FlexomataInterface`.
#### Accessible Member Functions
- `const Grid* get_grid() const`:
Get access to the associated `Grid` object.
- `const Enforcer* get_enforcer() const`:
Get access to the associated `Enforcer` object. Throws an exception if no rule is attached.
- `void attach_rule(const FlexomataTypes::RuleFunc& rule)`:
Attach a rule to the simulation interface. Creates an `Enforcer` object using the associated rule. Rule can be changed any number of times at run-time.
- `FlexomataInterface(const int argc, char** argv)`:
Constructor to initialize the simulation handler using initial configuration specified in a file from the terminal, specifically the second argument. Example: `./FlexomataApp path/to/config/file.txt`.

In the absence of the argument, Flexomata looks for `config.txt` in the current working directory, and if it exists, attempts to load the initial configuration from that.
- `FlexomataInterface(const std::string& config_text)`: 
Constructor to initialize the simulation handler using initial configuration specified in a string.

### `FlexomataTypes` (`types.h`)
Namespace for Flexomata-specific types.
- `typedef std::function<size_t(size_t, size_t)> RuleFunc`:
Type for functions that specify the cellular automata rules.

### `FlexomataErrors` (`flexomata.h`)
Namespace for error-handling.
#### Accessible Member Functions
- `void handle_exception(const std::exception& e)`:
Handles passed in exception. It is expected that the code involving interactions with Flexomata is structure in the following manner:
```C++
try {
    // Interact with Flexomata here
} catch (const std::exception& e) {
    FlexomataErrors::handle_exception(e);
}
```

### `Grid` (`grid.h`)
Handles the cellular automata grid. Accessible member functions allow reading the current state and dimensions.

Exhibits a "toroidal", wrap-around behavior on the boundaries.
#### Enums
```C++
enum Direction {
        TOP_LEFT = 0,
        TOP = 1,
        TOP_RIGHT = 2,
        LEFT = 3,
        RIGHT = 4,
        BOTTOM_LEFT = 5,
        BOTTOM = 6,
        BOTTOM_RIGHT = 7
};
```
#### Accessible Member Functions
- `bool is_initialized() const`: 
Check whether the `Grid` object is initialized.
- `size_t get_width() const`:
Get the number of columns of the grid.
- `size_t get_height() const`:
Get the number of rows of the grid.
- `void print_data() const`
Print the grid in its current state to the command line.
- `size_t get_pixel(const size_t x, const size_t y) const`
Get the value of a specific cell on the grid.
- `size_t get_neighbor(const size_t x, const size_t y, enum Direction dir) const`:
Get the value/state of a specific neighbor of a particular cell location on the grid.
- `size_t get_neighbor_count(const size_t x, const size_t y, const size_t of_state) const`
Get the number of neighboring cells of a specific value/state.

### `Enforcer` (`enforcer.h`)
#### Accessible Member Functions
- `void enforce_once() const`: 
Apply the rule to the grid once.
- `void enforce(size_t by_steps) const`:
Apply the rule to the grid a specific number of times.

## Configuration Parsing
Each instance of `FlexomataInterface`, and hence each simulation instance, must be initialized with a configuration string. The configurations string is either passed on explicitly, or read from a file. As of now, the configuration only specifies the initial state of the grid. That is to say, it specifies the value or state of each cell in the grid, represented as a non-negative integer.

The block specifying the grid configuration must begin with the `GRID` keyword, and only that keyword, in a single line. It must be followed by rows of non-negative integers separated by whitespace. Each row must have the same number of integers to maintain consistency.

Optionally, the block can be explicitly closed with the `END_GRID` keyword. This is completely unnecessary as of now, however.

### Example of a Configuration File
```
GRID
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
END_GRID
```

# Installation and Usage Instructions
## Build Instructions
```
git clone https://github.com/EcSolticia/Flexomata.git
cd Flexomata
mkdir build
cd build
cmake ..
make
```

# Usage Example
## Conway's Game of Life: Glider
```C++
#include "flexomata.h"
#include <unistd.h>

const size_t microsecond = 1000000;

int main() {
    std::string config = "GRID\n"
                         "0 1 0 0 0 0 0 0 0 0\n"
                         "0 0 1 0 0 0 0 0 0 0\n"
                         "1 1 1 0 0 0 0 0 0 0\n"
                         "0 0 0 0 0 0 0 0 0 0\n"
                         "0 0 0 0 0 0 0 0 0 0\n";

    try {
        FlexomataInterface sim(config);
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
        const Enforcer* enforcer_ptr = sim.get_enforcer();

        int steps = 100;
        while (steps-- > 0) {
            usleep(microsecond * 0.25);
            enforcer_ptr->enforce_once();
            grid_ptr->print_data();
            std::cout << "-----" << std::endl;
        }
    } catch (const std::exception& e) {
        FlexomataErrors::handle_exception(e);
    }

    return 0;
}
```
