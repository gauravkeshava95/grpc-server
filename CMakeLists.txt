cmake_minimum_required(VERSION 3.16)
project(grpc_server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get Homebrew prefix 
execute_process(
    COMMAND brew --prefix
    OUTPUT_VARIABLE HOMEBREW_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_PREFIX_PATH "${HOMEBREW_PREFIX}")

find_package(gRPC CONFIG REQUIRED)

# Get protoc and grpc_cpp_plugin paths from Homebrew directly
set(PROTOC_EXECUTABLE "${HOMEBREW_PREFIX}/bin/protoc")
set(GRPC_CPP_PLUGIN  "${HOMEBREW_PREFIX}/bin/grpc_cpp_plugin")

# Proto file
get_filename_component(PROTO_FILE "${CMAKE_SOURCE_DIR}/proto/greeter.proto" ABSOLUTE)
get_filename_component(PROTO_DIR  "${PROTO_FILE}" DIRECTORY)

set(PROTO_SRCS "${CMAKE_BINARY_DIR}/greeter.pb.cc")
set(PROTO_HDRS "${CMAKE_BINARY_DIR}/greeter.pb.h")
set(GRPC_SRCS  "${CMAKE_BINARY_DIR}/greeter.grpc.pb.cc")
set(GRPC_HDRS  "${CMAKE_BINARY_DIR}/greeter.grpc.pb.h")

add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS}
    COMMAND ${PROTOC_EXECUTABLE}
        --grpc_out="${CMAKE_BINARY_DIR}"
        --cpp_out="${CMAKE_BINARY_DIR}"
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
        -I "${PROTO_DIR}"
        "${PROTO_FILE}"
    DEPENDS "${PROTO_FILE}"
)

# Collect all source files
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")

add_executable(grpc_server
    ${APP_SOURCES}
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_include_directories(grpc_server PRIVATE
    ${CMAKE_BINARY_DIR}
    src/
)

target_link_libraries(grpc_server
    gRPC::grpc++
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)