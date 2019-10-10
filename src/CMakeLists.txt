cmake_minimum_required(VERSION 3.15)
project(car_crash)

find_package(SFML2 COMPONENTS sfml-graphics sfml-window sfml-system sfml-audio REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML2_INCLUDE})

target_link_libraries(${PROJECT_NAME}
        ${SFML2_LIBRARIES}
        )


