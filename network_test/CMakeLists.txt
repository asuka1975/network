cmake_minimum_required(VERSION 3.16)
project(network_test)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(network_test_run test.cpp)

target_link_libraries(network_test_run network gtest gmock -pthread)

target_include_directories(network_test_run PUBLIC ${NETWORK_INCLUDE_DIR})