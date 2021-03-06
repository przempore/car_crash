if (MSVC)
    add_definitions(-D_WIN32_WINNT=0x600)
endif ()

find_package(SFML COMPONENTS graphics window system REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(protobuf_MODULE_COMPATIBLE2 TRUE)
find_package(protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

get_filename_component(cc_proto "${PROTO_DIR}/car_crash.proto" ABSOLUTE)
get_filename_component(cc_proto_path "${cc_proto}" PATH)

set(cc_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.pb.cc")
set(cc_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.pb.h")
set(cc_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.grpc.pb.cc")
set(cc_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/car_crash.grpc.pb.h")

set(CMAKE_TOOLCHAIN_FILE_LENGTH 0)
string(LENGTH ${CMAKE_TOOLCHAIN_FILE} CMAKE_TOOLCHAIN_FILE_LENGTH)
set(VCPKG_FROM_PARENT_DIR_LENGTH 0)
string(LENGTH "scripts/buildsystems/vcpkg.cmake" VCPKG_FROM_PARENT_DIR_LENGTH)
set(CMAKE_TOOLCHAIN_DIR "")
math(EXPR CMAKE_TOOLCHAIN_FILE_LENGTH "${CMAKE_TOOLCHAIN_FILE_LENGTH}-${VCPKG_FROM_PARENT_DIR_LENGTH}" OUTPUT_FORMAT DECIMAL)
string(SUBSTRING ${CMAKE_TOOLCHAIN_FILE} 0 ${CMAKE_TOOLCHAIN_FILE_LENGTH} CMAKE_TOOLCHAIN_DIR)

if (WIN32)
    set(SYSTEM "windows")
elseif (UNIX)
    set(SYSTEM "linux")
endif ()
set(PROTO_INCLUDE "${CMAKE_TOOLCHAIN_DIR}/installed/x64-${SYSTEM}/include")

add_custom_command(
        OUTPUT "${cc_proto_srcs}" "${cc_proto_hdrs}" "${cc_grpc_srcs}" "${cc_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${cc_proto_path}" -I "${PROTO_INCLUDE}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${cc_proto}"
        DEPENDS "${cc_proto}"
)

set(COMMON_SOURCE
        framework/network/rectangle.cpp
        ${cc_proto_srcs}
        ${cc_grpc_srcs}
        )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}_client
        ${CMAKE_CURRENT_SOURCE_DIR}/client.cpp
        framework/graphics/render_window.cpp
        framework/graphics/rectangle_shape.cpp
        framework/graphics/color.cpp
        framework/graphics/mainLoop.cpp
        framework/utilities/collision_detection.cpp
        game/car_crash.cpp

        framework/network/cc_client.cpp
        ${COMMON_SOURCE}
        )

target_link_libraries(${PROJECT_NAME}_client
        sfml-graphics sfml-window sfml-system
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        )

# # server
add_executable(${PROJECT_NAME}_server
        ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
        framework/network/cc_server.cpp

        ${COMMON_SOURCE}
        )

target_link_libraries(${PROJECT_NAME}_server
        sfml-graphics sfml-window sfml-system
        ${_GRPC_GRPCPP_UNSECURE}
        ${_PROTOBUF_LIBPROTOBUF}
        )
