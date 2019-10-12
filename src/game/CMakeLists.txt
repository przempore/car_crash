cmake_minimum_required(VERSION 3.14)
project(game_application)

add_library(${PROJECT_NAME} OBJECT)

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/game_application.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/game_application.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/input.hpp>
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML2_INCLUDE})

add_subdirectory(wrappers)
