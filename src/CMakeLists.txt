cmake_minimum_required(VERSION 3.28.3)
Project(flexomata)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp grid/grid.cpp simulation/simulation_core.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})