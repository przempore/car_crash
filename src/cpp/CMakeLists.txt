cmake_minimum_required(VERSION 3.14)
project(car_crash)

find_package(SFML2 COMPONENTS sfml-graphics sfml-window sfml-system sfml-audio REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(framework)
add_subdirectory(game)

# client
add_executable(${PROJECT_NAME}_client)

target_sources(${PROJECT_NAME}_client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/client.cpp>
        )

target_include_directories(${PROJECT_NAME}_client
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framework
               ${CMAKE_CURRENT_SOURCE_DIR}/game
        SYSTEM PRIVATE ${SFML2_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME}_client
        $<TARGET_OBJECTS:game_impl>
        $<TARGET_OBJECTS:sfml_wrappers>
        $<TARGET_OBJECTS:cc_network>
        $<TARGET_OBJECTS:utilities>
        ${SFML2_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        )

# server
include_directories("${CMAKE_CURRENT_BINARY_DIR}/framework/network/")

add_executable(${PROJECT_NAME}_server)

target_sources(${PROJECT_NAME}_server PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server.cpp>
        )

target_include_directories(${PROJECT_NAME}_server
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framework
               ${CMAKE_CURRENT_SOURCE_DIR}/game
        SYSTEM PRIVATE ${SFML2_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME}_server
        $<TARGET_OBJECTS:cc_network>
        $<TARGET_OBJECTS:game_impl>
        $<TARGET_OBJECTS:sfml_wrappers>
        $<TARGET_OBJECTS:utilities>
        ${SFML2_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        )
