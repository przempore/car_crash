cmake_minimum_required(VERSION 3.15)
project(car_crash)

set(CMAKE_CXX_STANDARD 17)

add_executable(car_crash main.cpp)

target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        )
