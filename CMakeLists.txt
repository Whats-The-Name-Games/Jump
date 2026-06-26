cmake_minimum_required(VERSION 4.2)
project(jump)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.10
        FIND_PACKAGE_ARGS NAMES SDL3
)

FetchContent_MakeAvailable(SDL3)

add_subdirectory(src)

target_link_libraries(jump PRIVATE
    SDL3::SDL3
)