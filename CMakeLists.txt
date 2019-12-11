cmake_minimum_required(VERSION 3.10)

# set project name and version
project(Graphs VERSION 0.1)

# specify c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -O0)

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


add_executable(AdjM ${PROJECT_SOURCE_DIR}/src/adj_mat.cpp)
add_executable(DijSearch ${PROJECT_SOURCE_DIR}/src/dijkstras.cpp)
add_executable(Traversals ${PROJECT_SOURCE_DIR}/src/traversals.cpp)
add_executable(GraphDisplay ${PROJECT_SOURCE_DIR}/src/graphdisplay.cpp)
add_executable(LargeTest ${PROJECT_SOURCE_DIR}/src/large-test.cpp)
add_executable(Prims ${PROJECT_SOURCE_DIR}/src/testPrims.cpp)

target_include_directories(Traversals PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(GraphDisplay PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/boost_1_71_0 ${PROJECT_SOURCE_DIR}/graphviz)
target_include_directories(AdjM PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(DijSearch PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(LargeTest PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/boost_1_71_0 ${PROJECT_SOURCE_DIR}/graphviz)
target_include_directories(Prims PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/boost_1_71_0 ${PROJECT_SOURCE_DIR}/graphviz)

