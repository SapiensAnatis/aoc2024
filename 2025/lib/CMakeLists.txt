add_library(aoc_lib)

option(DEBUG_PRINT_ENABLED "Enable debug print" 0)

if (${DEBUG_PRINT_ENABLED})
  target_compile_definitions(aoc_lib PUBLIC DEBUG_PRINT_ENABLED)
endif()

target_sources(aoc_lib PRIVATE
  vector.h vector.c
  debug.h debug.c
  file.h file.c
  string_split.h string_split.c
  string.h string.c
)
target_include_directories(aoc_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
