cmake_minimum_required(VERSION 3.14)
project(sfml_wrappers)

add_library(${PROJECT_NAME} OBJECT)

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/render_window.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/render_window.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/rectangle_shape.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/rectangle_shape.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/color.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/color.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mainLoop.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mainLoop.cpp>
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${SFML2_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${SFML2_LIBRARIES}
        )
