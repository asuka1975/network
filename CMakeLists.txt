cmake_minimum_required(VERSION 3.16)
project(network)

set(CMAKE_CXX_STANDARD 17)


add_library(network include/network.h include/circuitable.h include/output.h include/neuron.h include/synapse.h
        src/network.cpp src/output.cpp src/synapse.cpp src/neuron.cpp)
target_include_directories(network PUBLIC include)