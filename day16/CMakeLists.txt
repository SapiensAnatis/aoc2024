configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example2.txt" "${CMAKE_CURRENT_BINARY_DIR}/example2.txt" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)
endif ()

add_executable(day16_test day16.cpp
        day16_test.cpp
        day16.h)

target_link_libraries(day16_test gtest_main)
