cmake_minimum_required(VERSION 2.8.7)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resource" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
file(GLOB SOURCES "*.c")
include_directories(${OCTASPIRE_DERN_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_executable(octaspire-maze-test-runner ${SOURCES})
set_property(TARGET octaspire-maze-test-runner PROPERTY C_STANDARD 99)
set_property(TARGET octaspire-maze-test-runner PROPERTY C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c99 -Wall -Wextra -pedantic -Werror")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")

if(OCTASPIRE_MAZE_COVERAGE)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif(OCTASPIRE_MAZE_COVERAGE)

target_link_libraries(octaspire-maze-test-runner octaspire_dern octaspire_core)

add_test(octaspire-maze-test-runner octaspire-maze-test-runner)
