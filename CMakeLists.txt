cmake_minimum_required (VERSION 2.6)
project (leptunit C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(leptunit SHARED leptunit.c)
add_executable(test-leptunit test-leptunit.c)
target_link_libraries(test-leptunit leptunit)
