configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example2.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/example2.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example3.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/example3.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example4.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/example4.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example5.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/example5.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example6.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/example6.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example7.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/example7.txt" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/day10/input.txt" COPYONLY)
endif ()

target_sources(aoc PRIVATE
    day10.cpp
    day10.h
    day10_test.cpp
)
