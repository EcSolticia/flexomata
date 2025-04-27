cmake_minimum_required(VERSION 3.10)

Project(Flexomata CXX)

add_library(${PROJECT_NAME} STATIC
    src/flexomatainterface.cpp
    src/grid.cpp
    src/configloader.cpp
    src/enforcer.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
