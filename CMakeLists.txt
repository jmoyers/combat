cmake_minimum_required (VERSION 3.5)
project(combat VERSION 0.0.1)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(combat_lib include/logs.hpp)

set_target_properties(combat_lib PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS ON
  LINKER_LANGUAGE CXX
)

add_executable(combat src/main.cpp)

set_target_properties(combat PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS ON
)
enable_testing()

add_subdirectory(test)