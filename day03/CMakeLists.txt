configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example2.txt" "${CMAKE_CURRENT_BINARY_DIR}/example2.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)

add_executable(day03_test day03.cpp
        day03_test.cpp
        day03.h)

target_link_libraries(day03_test gtest_main)