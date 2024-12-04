configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example.txt "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

add_executable(day2_test day2.cpp
        day2_test.cpp
        day2.h)

target_link_libraries(day2_test gtest_main)