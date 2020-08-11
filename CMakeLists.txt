cmake_minimum_required(VERSION 3.16)
project(network)

set(CMAKE_CXX_STANDARD 17)

set(NETWORK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_library(network include/network.h include/circuitable.h include/output.h include/neuron.h include/synapse.h
        src/network.cpp src/output.cpp src/synapse.cpp src/neuron.cpp
        src/graph_algorithm.cpp
        src/feedforward.cpp)
target_include_directories(network PUBLIC include)

add_subdirectory(network_test)