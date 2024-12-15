configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)

add_executable(day05_test day05.cpp
        day05_test.cpp
        day05.h)

target_link_libraries(day05_test gtest_main)