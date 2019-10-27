cmake_minimum_required(VERSION 3.14)
project(cc_grpc C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (GRPC_AS_SUBMODULE)
    set(_PROTOBUF_LIBPROTOBUF libprotobuf)
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
    set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
else ()
    set(protobuf_MODULE_COMPATIBLE TRUE)
    find_package(Protobuf CONFIG REQUIRED)
    message(STATUS "Using protobuf ${protobuf_VERSION}")

    set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

    # Find gRPC installation
    # Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
    find_package(gRPC CONFIG REQUIRED)
    message(STATUS "Using gRPC ${gRPC_VERSION}")

    set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif ()

get_filename_component(cc_proto "proto/car_crash.proto" ABSOLUTE)
get_filename_component(cc_proto_path "${cc_proto}" PATH)

set(cc_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.pb.cc")
set(cc_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.pb.h")
set(cc_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.grpc.pb.cc")
set(cc_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.grpc.pb.h")

add_custom_command(
        OUTPUT "${cc_proto_srcs}" "${cc_proto_hdrs}" "${cc_grpc_srcs}" "${cc_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${cc_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${cc_proto}"
        DEPENDS "${cc_proto}"
)

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")


add_library(${PROJECT_NAME} OBJECT)

target_sources(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cc_async_server.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cc_async_server.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cc_async_client.hpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cc_async_client.cpp>
        ${cc_proto_srcs}
        ${cc_grpc_srcs}
        )

target_link_libraries(${PROJECT_NAME}
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        )
