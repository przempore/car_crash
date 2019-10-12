cmake_minimum_required(VERSION 3.14)
project(car_crash)

find_package(SFML2 COMPONENTS sfml-graphics sfml-window sfml-system sfml-audio REQUIRED)

add_subdirectory(game)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
        main.cpp
        collision_detection.cpp
        collision_detection.hpp
        $<TARGET_OBJECTS:game_application>
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/game
        SYSTEM PRIVATE ${SFML2_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME} ${SFML2_LIBRARIES})
