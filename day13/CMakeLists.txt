configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)
endif ()

add_executable(day13_test day13.cpp
        day13_test.cpp
        day13.h)

target_link_libraries(day13_test gtest_main)
