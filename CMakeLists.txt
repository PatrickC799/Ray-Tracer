cmake_minimum_required(VERSION 3.25)

# Set project name and version
project(raytracer_start_2 VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include the core headers and source files
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Cameras)
include_directories(${CMAKE_SOURCE_DIR}/Core)
include_directories(${CMAKE_SOURCE_DIR}/Lights)
include_directories(${CMAKE_SOURCE_DIR}/Materials)
include_directories(${CMAKE_SOURCE_DIR}/Objects)
include_directories(${CMAKE_SOURCE_DIR}/Shaders)
include_directories(${CMAKE_SOURCE_DIR}/Textures)

# Add the core source files
file(GLOB CORE_SOURCES
        "linedrawer.cpp"
        "Cameras/*.cpp"
        "Core/*.cpp"
        "Lights/*.cpp"
        "Materials/*.cpp"
        "Objects/*.cpp"
        "Shaders/*.cpp"
        "Textures/*.cpp"
)

# Add the core header files
file(GLOB CORE_HEADERS
        "linedrawer.h"
        "Cameras/*.h"
        "Core/*.h"
        "Lights/*.h"
        "Materials/*.h"
        "Objects/*.h"
        "Shaders/*.h"
        "Textures/*.h"
)

# Compile and link executables for each main file along with core files
add_executable(MainLab1 main_lab1.cpp ${CORE_SOURCES} ${CORE_HEADERS})
add_executable(MainLab2 main_lab2.cpp ${CORE_SOURCES} ${CORE_HEADERS})
add_executable(MainLab34 main_lab34.cpp ${CORE_SOURCES} ${CORE_HEADERS})