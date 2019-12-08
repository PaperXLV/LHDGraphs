cmake_minimum_required(VERSION 3.10)

# set project name and version
project(Graphs VERSION 0.1)

# specify c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -O3)

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_executable(Traversals ${PROJECT_SOURCE_DIR}/src/traversals.cpp)
add_executable(AdjM ${PROJECT_SOURCE_DIR}/src/adj_mat.cpp)

target_include_directories(Traversals PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(AdjM PUBLIC ${PROJECT_SOURCE_DIR}/include)
