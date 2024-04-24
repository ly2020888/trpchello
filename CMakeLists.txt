cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(TRPC_INSTALL_PATH /usr/local/trpc-cpp/trpc)

# 加载tRPC-Cpp头文件及库路径
include(${TRPC_INSTALL_PATH}/cmake/config/trpc_config.cmake)
include(${TRPC_INSTALL_PATH}/cmake/tools/trpc_utils.cmake)

include_directories(${TRPC_INSTALL_PATH}/include)
include_directories(${CMAKE_SOURCE_DIR}/university)

# 链接服务库
link_directories(${TRPC_INSTALL_PATH}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

#---------------------------------------------------------------------------------------
# Compile project
#---------------------------------------------------------------------------------------
project(trcphello)

# 添加trpc库及其依赖的三方
set(LIBRARY trpc protolib studentlib ${LIBS_BASIC})
add_subdirectory(${CMAKE_SOURCE_DIR}/university)
add_subdirectory(${CMAKE_SOURCE_DIR}/manager)

add_executable(trcphello main.cpp university_service.h university_service.cc)

# 在您的构建目标里link trpc库
target_link_libraries(trcphello ${LIBRARY})

add_executable(trcphello_client client/fiber_client.cpp)

target_link_libraries(trcphello_client ${LIBRARY})
