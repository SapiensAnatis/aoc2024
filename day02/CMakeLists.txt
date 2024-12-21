configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example.txt "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/input.txt" COPYONLY)
endif ()

add_executable(day02_test day02.cpp
        day02_test.cpp
        day02.h)

target_link_libraries(day02_test gtest_main)