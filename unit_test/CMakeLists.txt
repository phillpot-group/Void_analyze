include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(utest utest.cpp ${PROJECT_SOURCE_DIR}/src/is_in_circle.cpp)
target_link_libraries(utest settings)
add_test(NAME utest COMMAND utest WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
