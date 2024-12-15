configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)

add_executable(day07_test day07.cpp
        day07_test.cpp
        day07.h)

target_link_libraries(day07_test gtest_main)