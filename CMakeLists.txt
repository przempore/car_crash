cmake_minimum_required(VERSION 3.15)

if (NOT CMAKE_TOOLCHAIN_FILE)
    message(WARNING "Consider using vcpkg and setup CMAKE_TOOLCHAIN_FILE accordingly.")
endif ()

# enable cache system
include(cmake/Cache.cmake)

project(car_crash CXX)

set(CMAKE_CXX_STANDARD 20)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif ()
endif ()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
    # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
    #
    # consider breaking this out per project as necessary
    target_precompile_headers(
            project_options
            INTERFACE
            <vector>
            <string>
            <map>
            <utility>)
endif ()

if (ENABLE_FUZZING)
    message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
    add_subdirectory(fuzz_test)
endif ()

set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/proto)
add_subdirectory(src/cpp)


#
#
#
#
#set(THIRD_PARTY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
#set(THIRD_PARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party)
#
#if (UNIX)
#    set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
#    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#endif()
#
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
#set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")
#
#add_subdirectory(third_party)
#
#if(GRPC_AS_SUBMODULE)
#    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/grpc ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)
#    set(_PROTOBUF_LIBPROTOBUF libprotobuf)
#    set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
#    set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
#    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
#else()
#    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
#    set(protobuf_MODULE_COMPATIBLE TRUE)
#    find_package(Protobuf CONFIG REQUIRED)
#    message(STATUS "Using protobuf ${protobuf_VERSION}")
#
#    set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
#    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
#
#    find_package(gRPC CONFIG REQUIRED)
#    message(STATUS "Using gRPC ${gRPC_VERSION}")
#
#    set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
#    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
#endif()
#
#add_subdirectory(src)
