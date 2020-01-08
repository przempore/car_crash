cmake_minimum_required(VERSION 3.14)
project(game_application C CXX)

set(CMAKE_CXX_STANDARD 17)
add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/i_game_application.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/input.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/collision_detection.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/collision_detection.cpp>
        $<TARGET_OBJECTS:cc_grpc>
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML2_INCLUDE})
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX) # todo: is it necessery if project defines language?

target_link_libraries(${PROJECT_NAME}
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        )


add_subdirectory(graphics)
add_subdirectory(network)
