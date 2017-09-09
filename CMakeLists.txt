cmake_minimum_required(VERSION 2.8.12)
project(octaspire-maze C)

set(OCTASPIRE_MAZE_CONFIG_VERSION_MAJOR 0)
set(OCTASPIRE_MAZE_CONFIG_VERSION_MINOR 96)
set(OCTASPIRE_MAZE_CONFIG_VERSION_PATCH 0)

message("== Building ${PROJECT_NAME} ${OCTASPIRE_MAZE_CONFIG_VERSION_MAJOR}.${OCTASPIRE_MAZE_CONFIG_VERSION_MINOR}.${OCTASPIRE_MAZE_CONFIG_VERSION_PATCH}")

set(OCTASPIRE_MAZE_CONFIG_TEST_RES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test/resource/")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/octaspire/maze/octaspire_maze_config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/maze/octaspire_maze_config.h")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel. " FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(EXISTS "${CMAKE_SOURCE_DIR}/.gitmodules")
    message("== Updating git submodules of ${PROJECT_NAME}...")
    message("-----------------------------------------------")
    execute_process(
        COMMAND git submodule update --init --recursive --remote
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    message("== Submodules of ${PROJECT_NAME} updated")
    message("-----------------------------------------------")
endif()

message("== Build type of ${PROJECT_NAME} is ${CMAKE_BUILD_TYPE}")

if(NOT TARGET octaspire-dern)
    message("== Project ${PROJECT_NAME} adding subdirectory:")
    message("-----------------------------------------------")
    add_subdirectory(external/octaspire_dern)
    message("-----------------------------------------------")
endif(NOT TARGET octaspire-dern)

if(NOT TARGET octaspire-easing)
    message("== Project ${PROJECT_NAME} adding subdirectory:")
    message("-----------------------------------------------")
    add_subdirectory(external/octaspire_easing)
    message("-----------------------------------------------")
endif(NOT TARGET octaspire-easing)

if(NOT TARGET octaspire-sdl2-utils)
    message("== Project ${PROJECT_NAME} adding subdirectory:")
    message("-----------------------------------------------")
    add_subdirectory(external/octaspire_sdl2_utils)
    message("-----------------------------------------------")
endif(NOT TARGET octaspire-sdl2-utils)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/octaspire/maze/*.h")
file(GLOB MANUAL6 "${CMAKE_CURRENT_SOURCE_DIR}/doc/man/man3/octaspire-dern.6")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/build/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_dern/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_dern/build/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_easing/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_easing/build/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_sdl2_utils/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_sdl2_utils/build/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
include_directories(${SDL2_INCLUDE_DIR})

add_executable(octaspire-xxd "${CMAKE_CURRENT_SOURCE_DIR}/etc/octaspire_xxd.c")
set_property(TARGET octaspire-xxd PROPERTY C_STANDARD 99)
set_property(TARGET octaspire-xxd PROPERTY C_EXTENSIONS OFF)
target_link_libraries(octaspire-xxd octaspire-core m)

option(OCTASPIRE_MAZE_COVERAGE  "OCTASPIRE_MAZE_COVERAGE"  OFF)
option(OCTASPIRE_MAZE_UNIT_TEST "OCTASPIRE_MAZE_UNIT_TEST" ON)

if(OCTASPIRE_MAZE_COVERAGE)
    message("== Code coverage enabled for ${PROJECT_NAME}")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif(OCTASPIRE_MAZE_COVERAGE)

if(OCTASPIRE_MAZE_UNIT_TEST)
    message("== Unit testing enabled for ${PROJECT_NAME}")
else()
    message("== Unit testing disabled for ${PROJECT_NAME}")
endif(OCTASPIRE_MAZE_UNIT_TEST)

add_executable(octaspire-maze ${SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/maze/octaspire_maze_animations.c" "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/maze/octaspire_maze_ini.c" "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/maze/octaspire_maze_texture_entities.c")
set_property(TARGET octaspire-maze PROPERTY C_STANDARD 99)
set_property(TARGET octaspire-maze PROPERTY C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c99 -fno-omit-frame-pointer -Wall -Wextra -pedantic -Werror")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
    #set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fcolor-diagnostics -fsanitize=undefined")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fcolor-diagnostics")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang")

target_link_libraries(octaspire-maze octaspire-easing octaspire-sdl2-utils octaspire-dern octaspire-core m)
install(TARGETS octaspire-maze DESTINATION bin)
install(FILES ${MANUAL6} DESTINATION "man/man6")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/maze/octaspire_maze_animations.c"
    COMMAND octaspire-xxd octaspire_maze_animations "${CMAKE_CURRENT_SOURCE_DIR}/res/animations.dern"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/res/animations.dern" octaspire-xxd
    COMMENT "Building header for resource: animation")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/maze/octaspire_maze_ini.c"
    COMMAND octaspire-xxd octaspire_maze_ini "${CMAKE_CURRENT_SOURCE_DIR}/res/ini.dern"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/res/ini.dern" octaspire-xxd
    COMMENT "Building header for resource: ini")

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/octaspire/maze/octaspire_maze_texture_entities.c"
    COMMAND octaspire-xxd octaspire_maze_texture_entities "${CMAKE_CURRENT_SOURCE_DIR}/res/entities.bmp"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/res/entities.bmp" octaspire-xxd
    COMMENT "Building header for resource: entities")

add_custom_target(
    cppcheck-maze
    COMMAND cppcheck --std=c99 -I "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/include" "${CMAKE_CURRENT_SOURCE_DIR}/external/octaspire_core/include"
            --enable=warning,performance,portability
            --verbose --quiet ${SOURCES} ${HEADERS})

add_custom_target(
    vera-maze
    COMMAND vera++ --error ${SOURCES} ${HEADERS})

add_custom_target(
    new-release-maze
    COMMAND "${CMAKE_SOURCE_DIR}/etc/new-release.sh" "${CMAKE_SOURCE_DIR}")

add_custom_target(
    publish-release-maze
    COMMAND "${CMAKE_SOURCE_DIR}/etc/publish-release.sh" "${CMAKE_SOURCE_DIR}")

if(NOT TARGET octaspire-maze-test-runner AND OCTASPIRE_MAZE_UNIT_TEST)
    message("== Building of unit tests enabled for ${PROJECT_NAME}")
    enable_testing()
    include(CTest)
    add_subdirectory(test)
endif(NOT TARGET octaspire-maze-test-runner AND OCTASPIRE_MAZE_UNIT_TEST)


add_custom_target(
    book-maze
    COMMAND asciidoctor --backend=html5 "${CMAKE_CURRENT_SOURCE_DIR}/doc/book/Octaspire_Maze_Manual.adoc"
    COMMAND asciidoctor-pdf -a source-highlighter=pygments "${CMAKE_CURRENT_SOURCE_DIR}/doc/book/Octaspire_Maze_Manual.adoc")
