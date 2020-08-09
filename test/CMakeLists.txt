
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/include
)

add_definitions("-D_GLIBCXX_DEBUG")

set(TEST_SOURCES 
  ${PROJECT_SOURCE_DIR}/test/test_logs.cpp
  ${PROJECT_SOURCE_DIR}/test/test_pool.cpp
  ${PROJECT_SOURCE_DIR}/test/test_parse.cpp
)

add_executable(tests ${TEST_SOURCES})

set_target_properties(tests PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS ON
)

target_link_libraries(tests combat_lib gtest gtest_main)

add_custom_command(TARGET tests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/test/fixtures/ $<TARGET_FILE_DIR:tests>/fixtures)

