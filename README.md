# Flexomata

Flexomata is a simple framework for handling cellular automata simulation in C++ as a static library. The user may provide a "rule function" to operate per each grid cell along with an initial configuration. Flexomata can thereafter apply the rule to each cell and offers access to the evolved state of the grid.

> **Note**: In spite of being fully functional as is, Flexomata is still under initial development. Notably, its API could undergo multiple minor changes prior to finalization.

# Installation

## Supported Platforms
- Linux / MacOS / Unix-like systems (Using CMake + Make).
- Microsoft Windows (Using CMake + Make with MinGW).

## Build Instructions
### Prerequisites
Ensure that the following programs are installed on your system:
- CMake (version 3.10 or above).
- The Make build system.
    - Natively available on Linux/MacOS.
    - On Windows, use MinGW.
- A C++ compiler that supports C++17 (For example, g++11 or above).
    - Natively available on Linux/MacOS.
    - On Windows, use MinGW.
- Git (to clone the repository).

### Commands (Linux/MacOS)
If you installed `git`, `cmake`, `make`, and `g++` using a dedicated package manager, they are likely already added to `PATH`, and the associated commands should be accessible from your terminal. Otherwise, you might need some manual setup. 
```
git clone https://github.com/EcSolticia/Flexomata.git
cd Flexomata
mkdir build
cd build
cmake ..
make
```

### Commands (Windows)
Open a terminal emulator or command prompt where `git`, `cmake`, `make` (via MinGW), and `g++` (via MinGW) are accessible. You may have to add the appropriate MinGW `bin` directory to your system's `Path` environment variable.
```
git clone https://github.com/EcSolticia/Flexomata.git
cd Flexomata
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make
```

# Getting Started:  Hello, Flexomata!
A successful execution of the build instructions is expected to yield `libFlexomata.a` in directory `Flexomata/build`. To use the library in a project using CMake, you have to specify Flexomata's include directory and link your project to the generated library. 

The following portion of this section will exemplify the process through creating a simulation of Conway's Game of Life using Flexomata.

### 1. Create your project
```
mkdir GameOfLife
cd GameOfLife
touch main.cpp
touch CMakeLists.txt
```
### 2. Set up CMakeLists.txt
#### 1. Make sure to require a CMake version above 3.10 through
```CMake
cmake_minimum_required(VERSION 3.10)
```
If you intend to use or require newer CMake versions, you may replace the "3.10" with your desired version.
For this walkthrough, I will stick to 3.10.

#### 2. Set the name of your project, optionally specify the language (the "CXX" part).
```CMake
project(GameOfLife CXX)
```

#### 3. Tell CMake to build an executable from `main.cpp`.
```CMake
add_executable(${PROJECT_NAME} main.cpp)
```

#### 4. Specify the Flexomata include directories
```CMake
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/path/to/include
)
```
Make sure to replace the placeholder path `${CMAKE_CURRENT_SOURCE_DIR}/path/to/include` with the actual include directory in your system.

#### 5. Specify that the Flexomata library be linked to your project
```CMake
target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/path/to/lib/libFlexomata.a)
```

Again, be sure to replace the placeholder path `${CMAKE_CURRENT_SOURCE_DIR}/path/to/lib/libFlexomata.a` with the actual path to the library in your system.

#### 6. Specify the C++ standard to use
```CMake
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
```

Flexomata uses the C++17 standard.

#### Overall, we obtain:
```CMake
cmake_minimum_required(VERSION 3.10)

project(GameOfLife CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/path/to/include
)

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/path/to/lib/libFlexomata.a)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
```

This will direct how CMake generates our buildfiles.

### 3. Write the source file
The comments explain each segment of the code.
```C++
#include "flexomata.h" // the only header you have to directly include

int main() {
    // Specify the initial configuration
    // This is a "glider" in Conway's Game of Life
    // https://conwaylife.com/wiki/Glider
    const std::string config_text = "GRID\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 1 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 1 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 1 1 1 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";                                    

    try {

        // Create the entry point of the simulation and the interface
        Flexomata::SimulationScene sim = Flexomata::SimulationScene(config_text, Flexomata::SimulationScene::construct_from_text{});

        // Access the Grid object managed by the simulation handler, read-only
        const Flexomata::Grid* grid_ptr = sim.get_grid();

        // Represent the rules of Conway's Game of Life
        // https://conwaylife.com/wiki/Conway%27s_Game_of_Life#Rules
        FlexomataTypes::RuleFunc game_of_life = [grid_ptr](const size_t x, const size_t y) -> size_t {
            const size_t neighbor_count = grid_ptr->get_neighbor_count(x, y, 1);
            const size_t alive = grid_ptr->get_pixel(x, y);
            if (alive) {
                return (neighbor_count == 2 || neighbor_count == 3);
            } else {
                return (neighbor_count == 3);
            }
        };

        // Let the simulation know of the rule to enforce
        sim.set_rule(game_of_life);

        while (true) {
            // Do not execute the following blocks until the return key is pressed
            std::cin.get();
        
            // Simulate and present next step
            sim.enforce_rule_once();
            grid_ptr->print_data();
        }

    } catch (const std::exception& e) {
        // Self-explanatory: handle exceptions
        FlexomataErrors::handle_exception(e);
    }

    return 0;
}
```

### 4. Compile your executable and run!
In your project directory, create a new directory named `build`, change directory to `build` (`cd build`), and run
```
cmake ..
```
on Linux/MacOS to generate the Makefiles, and
```
cmake -G "MinGW Makefiles" ..
```
On Windows to generate the MinGW Makefiles.

Finally, run
```
make
```
In the `build` directory, which should link the library and compile your executable.

You may wish to run the executable to see if it behaves as expected.

> The program we built here simulates Conway's Game of Life on our initial configuration Grid and pattern. Press enter to simulate the next step. Pressing Ctrl + C, or a similar key combination depending on your terminal and platform can be used to terminate the program.

# Usage Documentation
## Accessible Classes and Namespaces

### `Flexomata` (Namespace)
Encapsulates the core classes of Flexomata. 
These classes include:
    - `SimulationScene`.
    - `Grid`.
    - `DeferredConfigLoader`
    - `ConfigLoader` (an internal class used to handle config loading).
### `SimulationScene` (`flexomata.h`)
Belongs to the `Flexomata` namespace.

Creates a separate "scene" for a particular simulation, with predefined Grid dimensions and an initial configuration. Is the entry point for all pertinent simulation functionalities. Other accessible classes can only be accessed through an instance of `SimulationScene`.
#### Accessible Member Functions
- `const Grid* get_grid() const`:
Get access to the associated `Grid` object.
- `DeferredConfigLoader* get_deferred_configloader()`:
Get access to the `DeferredConfigLoader` object. Can be used to specify the config programmatically for it to be manually loaded through `DeferredConfigLoader::load_config_into_target`.
- `void set_rule(const FlexomataTypes::RuleFunc& rule)`:
Set the simulation rule. This will determine the specific cellular automata that is being simulated.
- `void enforce_rule_once()`:
Apply the simulation rule to the grid exactly once.
- `void enforce_rule(const size_t by_steps)`:
Apply the simuation rule to the grid exactly `by_steps` times.
- `SimulationScene(const int argc, char** argv)`:
Constructor to initialize the scene using initial configuration specified in a file from the terminal, specifically the second argument. Example: `./FlexomataApp path/to/config/file.txt`.

In the absence of the argument, Flexomata looks for `config.txt` in the current working directory, and if it exists, attempts to load the initial configuration from that.
- `SimulationScene(const std::string& config_text, construct_from_text)`: 
Constructor to initialize the scene using initial configuration specified in a string.
- `SimulationScene(const std::string& config_path, construct_from_predefined_path)`:
Constructor to initialize the scene using initial configuration from a predefined file (relative to the current working directory of the terminal).
- `SimulationScene(const size_t grid_width, const size_t grid_height, construct_from_deferred_config)`:
Constructor to initialize the scene without a predefiend configuration. Creates a `DeferredConfigLoader` object and allows access to it through `SimulationScene::get_deferred_configloader`.

#### Notes
- `SimulationScene` manages the memory of pertinent `Grid` and `DeferredConfigLoader` objects automatically. The former is currently stack-allocated. The latter is heap-allocated through a smart pointer, and hence is automatically freed as the `SimulationScene` object goes out of scope.
- To use Flexomata through the `SimulationScene` class, you have to include and only include `flexomata.h` from the include directory. 
- It may be possible to achieve a lower-level control over the behavior of the simulation by accessing the other classes more directly, but that is not tested. Furthermore, this is not something Flexomata is designed for and around, and hence is not documented as of now.

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
Belongs to the `Flexomata` namespace.

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

### `DeferredConfigLoader` (`deferred_configloader.h`)
Belongs to the `Flexomata` namespace.

#### Accessible Member Functions
- `void set_config_pixel(const size_t x, const size_t y, const size_t value)`:
Set the specific value of a cell on the initial grid configuration.
- `void load_config_into_target() const`:
Load the specified configuration into the target grid, as returned by `SimulationScene::get_grid`.

## Configuration Parsing
Each instance of `SimulationScene`, and hence each simulation instance, must be initialized with a configuration string. The configurations string is either passed on explicitly, or read from a file. As of now, the configuration only specifies the initial state of the grid. That is to say, it specifies the value or state of each cell in the grid, represented as a non-negative integer.

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

# License
Flexomata is distributed under the [MIT License](https://github.com/EcSolticia/Flexomata/blob/main/LICENSE).