cmake_minimum_required(VERSION 3.5)
project(combat VERSION 0.0.1)

add_definitions(-DNAPI_VERSION=3)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++ -fsanitize=memory -fsanitize-memory-track-origins")

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/node_modules/node-addon-api
  /usr/include/nodejs/src
  /home/jmoyers/dev/llvm-project/build/include
)

link_directories(
  /home/jmoyers/dev/llvm-project/build/lib
)

link_libraries(pthread c++abi)

add_library(combat_addon SHARED src/main.cpp ${CMAKE_JS_SRC})

add_library(combat_lib 
  include/logs.hpp
  include/pool.hpp
)

set_target_properties(combat_addon PROPERTIES 
  PREFIX ""
  SUFFIX ".node"
  CXX_STANDARD 17
  LINKER_LANGUAGE CXX
)

set_target_properties(combat_lib PROPERTIES 
  CXX_STANDARD 17
  LINKER_LANGUAGE CXX
)

add_subdirectory(test)
add_subdirectory(benchmarks)
add_subdirectory(vendor/googletest)
add_subdirectory(vendor/benchmark)
