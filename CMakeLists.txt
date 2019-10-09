cmake_minimum_required(VERSION 3.15)
project(car_crash)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third_party)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(THIRG_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

add_executable(car_crash main.cpp)

target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        )
