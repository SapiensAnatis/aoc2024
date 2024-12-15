configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)
endif ()

add_executable(day08_test day08.cpp
        day08_test.cpp
        day08.h)

target_link_libraries(day08_test gtest_main)