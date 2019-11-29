cmake_minimum_required(VERSION 3.14)
project(car_crash)

set(CMAKE_CXX_STANDARD 17)
set(THIRD_PARTY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(THIRD_PARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(third_party)

if(GRPC_AS_SUBMODULE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/grpc ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)
    set(_PROTOBUF_LIBPROTOBUF libprotobuf)
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
    set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
else()
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
    set(protobuf_MODULE_COMPATIBLE TRUE)
    find_package(Protobuf CONFIG REQUIRED)
    message(STATUS "Using protobuf ${protobuf_VERSION}")

    set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

    find_package(gRPC CONFIG REQUIRED)
    message(STATUS "Using gRPC ${gRPC_VERSION}")

    set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

add_subdirectory(src)
