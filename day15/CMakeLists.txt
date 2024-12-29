configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_BINARY_DIR}/day15/example.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example2.txt" "${CMAKE_CURRENT_BINARY_DIR}/day15/example2.txt" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/example3.txt" "${CMAKE_CURRENT_BINARY_DIR}/day15/example3.txt" COPYONLY)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input.txt" "${CMAKE_CURRENT_BINARY_DIR}/day15/input.txt" COPYONLY)
endif ()

target_sources(aoc PRIVATE
        day15.cpp
        day15.h
        day15_test.cpp
)
