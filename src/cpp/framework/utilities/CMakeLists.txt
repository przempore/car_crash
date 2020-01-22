cmake_minimum_required(VERSION 3.14)
project(utilities C CXX)

add_library(${PROJECT_NAME} OBJECT)


target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/collision_detection.cpp>
        )

target_include_directories(${PROJECT_NAME}
        SYSTEM PRIVATE ${SFML2_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME}
        $<TARGET_OBJECTS:sfml_wrappers>
        )
