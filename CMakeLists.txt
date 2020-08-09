cmake_minimum_required(VERSION 3.5)
project(combat VERSION 0.0.1)
add_definitions(-DNAPI_VERSION=3)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${CMAKE_JS_INC}
  ${PROJECT_SOURCE_DIR}/node_modules/node-addon-api
  /usr/include/nodejs/src
)

add_library(combat_addon SHARED src/main.cpp ${CMAKE_JS_SRC})
add_library(combat_lib 
  include/logs.hpp
  include/pool.hpp
)

set_target_properties(combat_addon PROPERTIES 
  PREFIX ""
  SUFFIX ".node"
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS ON
  LINKER_LANGUAGE CXX
)

set_target_properties(combat_lib PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS ON
  LINKER_LANGUAGE CXX
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(test)
add_subdirectory(vendor/googletest)
