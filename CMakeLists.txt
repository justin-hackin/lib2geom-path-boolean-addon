cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project (lib2geom-path-boolean-addon)
include_directories(${CMAKE_JS_INC})

# from https://foonathan.net/2016/07/cmake-dependency-handling/
execute_process(COMMAND git submodule update --init
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(lib2geom)

file(GLOB SOURCE_FILES "intersection.cc")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES 
        PREFIX "" 
        SUFFIX ".node"
        # POSITION_INDEPENDENT_CODE TRUE
        # suggested as per https://github.com/cmake-js/cmake-js/issues/204
        # does not fix error:
        # relocation R_X86_64_PC32 against symbol `_ZGVZN4Geom6chooseIdEET_jjE16pascals_triangle' can not be used when making a shared object; recompile with -fPIC
)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} 2Geom::2geom)

# Include N-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# define NPI_VERSION
add_definitions(-DNAPI_VERSION=3)
