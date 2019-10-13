cmake_minimum_required(VERSION 3.14)
project(car_crash)

set(CMAKE_CXX_STANDARD 17)
set(THIRD_PARTY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(THIRD_PARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(src)
