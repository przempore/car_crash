cmake_minimum_required(VERSION 3.14)
project(game_impl)

add_library(${PROJECT_NAME} OBJECT)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../framework/network/")

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/car_crash.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/car_crash.hpp>
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../framework
        ${SFML2_INCLUDE}
        )
