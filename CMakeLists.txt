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

# Find OpenMP
find_package(OpenMP REQUIRED)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Create the executable

add_executable(my_openmp_project ${SOURCES})
target_link_libraries(my_openmp_project PRIVATE OpenMP::OpenMP_CXX OpenSSL::SSL OpenSSL::Crypto)

find_package(OpenMP REQUIRED)
target_link_libraries(my_openmp_project PRIVATE OpenMP::OpenMP_CXX)
