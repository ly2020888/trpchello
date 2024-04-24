cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(TRPC_INSTALL_PATH /usr/local/trpc-cpp/trpc)

# 加载tRPC-Cpp头文件及库路径
include(${TRPC_INSTALL_PATH}/cmake/config/trpc_config.cmake)
include(${TRPC_INSTALL_PATH}/cmake/tools/trpc_utils.cmake)

include_directories(${TRPC_INSTALL_PATH}/include)
include_directories(${CMAKE_SOURCE_DIR})

set(PB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/student.proto)
set(PB_PROTOC ${TRPC_INSTALL_PATH}/bin/protoc)

#---------------------------------------------------------------------------------------
# Compile library
#---------------------------------------------------------------------------------------
project(studentlib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# @brief                            Generate corresponding .pb.cc and .pb.h stub code based on proto files
# @param OUT_PB_SRCS_FILES          [Output]The generated .pb.cc files from proto files
# @param GEN_PB_PROTO_FILES         [Input]The collection of proto files
# @param PROTOBUF_PROTOC_EXECUTABLE [Input]Protoc executable program generated during the compilation process in the build/bin directory
# @param CMAKESOURCEDIR             [Input]The directory where the CMakeLists.txt of the project is located
COMPILE_PROTO(OUT_PB_SRCS "${PB_SRC}" ${PB_PROTOC} ${CMAKE_CURRENT_SOURCE_DIR})

add_library(studentlib ${OUT_PB_SRCS} manager.cpp manager.h)
