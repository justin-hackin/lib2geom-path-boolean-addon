cmake_minimum_required(VERSION 3.0.0)

project(path-boolean VERSION 0.1.0)

add_library(${PROJECT_NAME} ../inkscape-lib2geom/build/src/2geom)
target_include_directories(${PROJECT_NAME} ../inkscape-lib2geom/include)
add_executable(${PROJECT_NAME} main.cpp)
