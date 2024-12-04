configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example.txt "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

add_executable(day2_run day2.cpp
        day2_test.cpp
        day2.h)

target_link_libraries(day2_run gtest_main)