cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

# 加载tRPC-Cpp头文件及库路径
include(${TRPC_INSTALL_PATH}/cmake/config/trpc_config.cmake)
include(${TRPC_INSTALL_PATH}/cmake/tools/trpc_utils.cmake)

include_directories(${TRPC_INSTALL_PATH}/include)
include_directories(${CMAKE_SOURCE_DIR})

#---------------------------------------------------------------------------------------
# Compile library
#---------------------------------------------------------------------------------------
project(protolib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(PB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/university.proto)
set(PB_PROTOC ${TRPC_INSTALL_PATH}/bin/protoc)
set(TRPC_CPP_PLUGIN ${TRPC_INSTALL_PATH}/bin/trpc_cpp_plugin)

# @brief                            Generate corresponding .pb.cc and .pb.h stub code based on proto files
# @param OUT_PB_SRCS_FILES          [Output]The generated .pb.cc files from proto files
# @param GEN_PB_PROTO_FILES         [Input]The collection of proto files
# @param PROTOBUF_PROTOC_EXECUTABLE [Input]Protoc executable program generated during the compilation process in the build/bin directory
# @param CMAKESOURCEDIR             [Input]The directory where the CMakeLists.txt of the project is located
COMPILE_PROTO(OUT_PB_SRCS "${PB_SRC}" ${PB_PROTOC} ${CMAKE_CURRENT_SOURCE_DIR})

# @brief                             Generate corresponding .trpc.pb.cc and .trpc.pb.h stub code based on proto files
# @param OUT_TRPC_PB_SRCS_FILES      [Output]The generated .trpc.pb.cc files from proto files
# @param GEN_TRPC_PB_PROTO_FILES     [Input]The collection of proto files
# @param PROTOBUF_PROTOC_EXECUTABLE  [Input]Protoc executable program generated during the compilation process in the build/bin directory
# @param TRPC_TO_CPP_PLUGIN          [Input]trpc_cpp_plugin executable program generated during the compilation process in the build/bin directory
# @param CMAKESOURCEDIR              [Input]The directory where the CMakeLists.txt of the project is located
TRPC_COMPILE_PROTO(OUT_TRPC_PB_SRCS "${PB_SRC}" ${PB_PROTOC} ${TRPC_CPP_PLUGIN} ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY trpc ${LIBS_BASIC})
add_library(protolib ${OUT_PB_SRCS} ${OUT_TRPC_PB_SRCS})

target_link_libraries(protolib ${LIBRARY})
