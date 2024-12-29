configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)
endif ()

add_executable(day25_test day25.cpp
        day25_test.cpp
        day25.h)

target_link_libraries(day25_test gtest_main)
