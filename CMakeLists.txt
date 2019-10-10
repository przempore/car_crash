cmake_minimum_required(VERSION 3.15)
project(car_crash)

set(CMAKE_CXX_STANDARD 17)
set(THIRD_PARTY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(THIRD_PARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)

add_subdirectory(third_party EXCLUDE_FROM_ALL)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(THIRG_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

add_subdirectory(src)
