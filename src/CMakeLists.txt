cmake_minimum_required(VERSION 3.14)
project(car_crash)

find_package(SFML2 COMPONENTS sfml-graphics sfml-window sfml-system sfml-audio REQUIRED)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/framework/network")

add_subdirectory(framework)
add_subdirectory(game)
find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

# client
add_executable(${PROJECT_NAME}_client)

target_sources(${PROJECT_NAME}_client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/client.cpp>
        $<TARGET_OBJECTS:sfml_wrappers>
        $<TARGET_OBJECTS:game_impl>
        )

target_include_directories(${PROJECT_NAME}_client
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framework
        ${CMAKE_CURRENT_SOURCE_DIR}/game
        SYSTEM PRIVATE ${SFML2_INCLUDE}
        )

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
message(STATUS "src: _GRPC_GRPCPP_UNSECURE=${_GRPC_GRPCPP_UNSECURE}")

target_link_libraries(${PROJECT_NAME}_client
        ${SFML2_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        game_application
        )

# server
add_executable(${PROJECT_NAME}_server)

target_sources(${PROJECT_NAME}_server PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server.cpp>
        $<TARGET_OBJECTS:sfml_wrappers>
        $<TARGET_OBJECTS:game_impl>
        )

target_include_directories(${PROJECT_NAME}_server
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/framework
               ${CMAKE_CURRENT_SOURCE_DIR}/game
        SYSTEM PRIVATE ${SFML2_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME}_server
        ${SFML2_LIBRARIES}
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        game_application
        )
