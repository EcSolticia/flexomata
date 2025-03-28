# Initializing a `SimCore` object

A `SimCore` object is responsible for handling simulation rules, execution and rendering in the program. Consequently, it relies on other classes like `Grid`, which itself relies on `StateManager` and `CoordSystem` to carry out the expected processes. A `SimCore` object "owns" a `Grid` through an `std::unique_ptr` object.
To initialize a `SimCore` class to usablity, use the following snippet with appropriate variable names. 

```cpp
SimCore sim_core_name = SimCore(your_rule_func);
sim_core_name.initialize_grid(your_width, your_height, your_side_length);
sim_core_name.initialize_state_manager(your_states_vector);
```

It is crucial that one calls the latter two functions in the snippet. It is conceptually nonsensical to try to simulate a square-cell grid-based Cellular Automata simulation to not have a valid grid, which is handled by `Grid` objects in **flexomata**. The `Grid` class uses `StateManager` objects to handle different kinds of `State` objects, which represent different states each cell can exhibit, and their core properties, such as color.
