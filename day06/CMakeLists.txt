configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)

add_executable(day06_test day06.cpp
        day06_test.cpp
        day06.h)

target_link_libraries(day06_test gtest_main)