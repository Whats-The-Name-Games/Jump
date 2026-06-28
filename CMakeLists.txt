cmake_minimum_required(VERSION 4.2)
project(jump)

# Ensure all our SDL libraries are compiled together with our binary
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

# Requires NASM to support AVIF, not worth the hassle
set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)

FetchContent_Declare(
        SDL3_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-3.4.4
        FIND_PACKAGE_ARGS NAMES SDL3_image
)

FetchContent_MakeAvailable(SDL3 SDL3_image)

add_subdirectory(src)

# Copy our assets into our output binary directory
FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/assets")

file(GLOB ASSETS "assets/*")

file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR}/assets)

# Now deal with potential libstdc++ problems on windows using mingw (if on msvc should be fine) (just use mscv)
if (MINGW)
    target_link_options(jump PRIVATE "-static-libstdc++" "-static-libgcc")
ENDIF()


if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

target_link_libraries(jump PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)