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
project(dblib)

set(LIBRARY trpc ${LIBS_BASIC})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
add_library(dblib database.cc database.h)
target_link_libraries(dblib ${LIBRARY})

add_executable(dblib_test
        ${CMAKE_CURRENT_SOURCE_DIR}/database.h
        ${CMAKE_CURRENT_SOURCE_DIR}/database_test.cc)

# ${LIB_GTEST_GMOCK} must be linked before ${LIBRARY}
target_link_libraries(dblib_test ${LIB_GTEST_GMOCK} dblib)

enable_testing()
add_test(NAME RedisServiceTest
        COMMAND dblib_test)