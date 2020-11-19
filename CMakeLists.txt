cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project (lib2geom-path-boolean-addon)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)

# from https://foonathan.net/2016/07/cmake-dependency-handling/
execute_process(COMMAND git submodule update --init
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(lib2geom EXCLUDE_FROM_ALL)

file(GLOB SOURCE_FILES "boolean.cc")

add_definitions("-std=c++11")
target_link_libraries(${PROJECT_NAME} 2Geom::2geom)
add_executable(client ${SOURCE_FILES})

set_target_properties(client PROPERTIES COMPILE_FLAGS "-s USE_BOOST_HEADERS=1" LINK_FLAGS "-s USE_BOOST_HEADERS=1")

