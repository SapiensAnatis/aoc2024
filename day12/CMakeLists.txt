configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/day12/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example2.txt" "${CMAKE_CURRENT_BINARY_DIR}/day12/example2.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example3.txt" "${CMAKE_CURRENT_BINARY_DIR}/day12/example3.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example4.txt" "${CMAKE_CURRENT_BINARY_DIR}/day12/example4.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example5.txt" "${CMAKE_CURRENT_BINARY_DIR}/day12/example5.txt" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/day12/input.txt" COPYONLY)
endif ()

target_sources(aoc PRIVATE
        day12.cpp
        day12.h
        day12_test.cpp
)
