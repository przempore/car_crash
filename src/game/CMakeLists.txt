cmake_minimum_required(VERSION 3.14)
project(game_application)

add_library(${PROJECT_NAME} OBJECT
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/game_application.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/game_application.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/input.hpp>
        )

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/game_application.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/game_application.hpp>
        )
