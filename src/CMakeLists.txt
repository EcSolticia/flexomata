cmake_minimum_required(VERSION 3.22.1)
Project(Flexomata)

add_executable(${PROJECT_NAME} main.cpp ConfigLoader/configloader.cpp Grid/grid.cpp Enforcer/enforcer.cpp flexomatainterface.cpp)