cmake_minimum_required(VERSION 3.10)

# Set the project name
project(my_openmp_project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
file(GLOB SOURCES
    src/*.cpp
)

# Create the executable
add_executable(my_openmp_project ${SOURCES})