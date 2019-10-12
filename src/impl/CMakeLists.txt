cmake_minimum_required(VERSION 3.14)
project(impl)

add_library(${PROJECT_NAME} OBJECT)

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/collision_detection.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/collision_detection.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/car_crash.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/car_crash.hpp>
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../game
        ${SFML2_INCLUDE}
        )
