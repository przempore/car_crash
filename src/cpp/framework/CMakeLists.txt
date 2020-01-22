cmake_minimum_required(VERSION 3.14)
project(game_framework C CXX)

set(CMAKE_CXX_STANDARD 17)
#add_library(${PROJECT_NAME} SHARED)
#
#target_sources(${PROJECT_NAME} PUBLIC
#        #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/i_game_application.hpp>
#        )
#
#target_include_directories(${PROJECT_NAME}
#        SYSTEM PRIVATE ${SFML2_INCLUDE}
#        )
#
#target_link_libraries(${PROJECT_NAME}
#        ${_GRPC_GRPCPP_UNSECURE}
#        ${_PROTOBUF_LIBPROTOBUF}
#        ${SFML2_LIBRARIES}
#        $<TARGET_OBJECTS:cc_network>
#        $<TARGET_OBJECTS:utilities>
#        )

add_subdirectory(network)
add_subdirectory(graphics)
add_subdirectory(utilities)
