cmake_minimum_required(VERSION 3.14)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/SFML)
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/SFML -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -GNinja
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SFML)

execute_process(COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/SFML --config ${CMAKE_BUILD_TYPE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SFML)

add_subdirectory(SFML EXCLUDE_FROM_ALL)

if(GRPC_AS_SUBMODULE)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/grpc)
	
	execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/grpc -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -GNinja
	        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/grpc)
	
	execute_process(COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/grpc --config ${CMAKE_BUILD_TYPE}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/grpc)
	
	add_subdirectory(grpc EXCLUDE_FROM_ALL)
	
  set(_PROTOBUF_LIBPROTOBUF libprotobuf)
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
  set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
else()
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})
  set(protobuf_MODULE_COMPATIBLE TRUE)
  find_package(Protobuf CONFIG REQUIRED)
#  find_package(Protobuf REQUIRED)
  message(STATUS "Using protobuf ${protobuf_VERSION}")

  set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

  # Find gRPC installation
  # Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
  find_package(gRPC CONFIG REQUIRED)
#  find_package(gRPC REQUIRED)
  message(STATUS "Using gRPC ${gRPC_VERSION}")

  set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()
