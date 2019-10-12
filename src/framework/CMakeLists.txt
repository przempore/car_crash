cmake_minimum_required(VERSION 3.14)
project(game_application)

set(CMAKE_CXX_STANDARD 17)
add_library(${PROJECT_NAME} OBJECT)

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/i_game_application.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/input.hpp>
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML2_INCLUDE})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


add_subdirectory(wrappers)
