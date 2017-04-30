cmake_minimum_required(VERSION 2.8.12)
project(octaspire-maze-test-runner C)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resource" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
file(GLOB SOURCES "*.c")
include_directories(${OCTASPIRE_DERN_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c99 -Wall -Wextra -pedantic -Werror")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")

if(OCTASPIRE_MAZE_COVERAGE)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif(OCTASPIRE_MAZE_COVERAGE)

if(NOT WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GREATEST_ENABLE_ANSI_COLORS=1)
    message("== Enabled ANSI colors for ${PROJECT_NAME}")
endif(NOT WIN32)

target_link_libraries(${PROJECT_NAME} octaspire-dern octaspire-core)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
