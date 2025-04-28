cmake_minimum_required(VERSION 3.10)

project(Rule30 CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../../build/libFlexomata.a)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)