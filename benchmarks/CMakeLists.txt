
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/vendor/benchmark/include
)

add_definitions("-D_GLIBCXX_DEBUG")

set(TEST_SOURCES 
  ${PROJECT_SOURCE_DIR}/benchmarks/parse.cpp
)

add_executable(benchmarks ${TEST_SOURCES})

set_target_properties(tests PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS ON
)

target_link_libraries(benchmarks combat_lib benchmark::benchmark)
