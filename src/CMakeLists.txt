cmake_minimum_required(VERSION 3.14)
project(car_crash)

find_package(SFML2 COMPONENTS sfml-graphics sfml-window sfml-system sfml-audio REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/collision_detection.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/collision_detection.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/impl/car_crash.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/impl/car_crash.hpp>
        $<TARGET_OBJECTS:game_application>
        $<TARGET_OBJECTS:sfml_wrappers>
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/game
        SYSTEM PRIVATE ${SFML2_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME}
        ${SFML2_LIBRARIES}
        )

add_subdirectory(game)
