find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_definitions("-D_GLIBCXX_DEBUG")

set(TEST_SOURCES 
  ${PROJECT_SOURCE_DIR}/test/main.cpp
  ${PROJECT_SOURCE_DIR}/test/test_logs.cpp
  ${PROJECT_SOURCE_DIR}/test/test_pool.cpp
  ${PROJECT_SOURCE_DIR}/test/test_parse.cpp
)
set(TEST_LIBS combat_lib)

add_executable(tests ${TEST_SOURCES})
set_target_properties(tests PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS ON
)
target_link_libraries(tests ${TEST_LIBS} ${Boost_LIBRARIES})
add_test(NAME logs_test COMMAND tests)