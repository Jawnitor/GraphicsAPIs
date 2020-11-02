cmake_minimum_required(VERSION 3.17)
project(01)

set(CMAKE_CXX_STANDARD 17)
link_libraries(SDL2)

add_executable(01 src/main.cpp)
