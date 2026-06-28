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

#set(USE_VENDORED_SDL 0 CACHE INTERNAL "")
#set(BUILD_SHARED_LIBS OFF)
#set(SDL_SHARED OFF)
#set(SDL_STATIC ON)

#set(SDLIMAGE_VENDORED ON)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)

FetchContent_Declare(
        SDL3_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-3.4.4
        FIND_PACKAGE_ARGS NAMES SDL3_image
)

FetchContent_MakeAvailable(SDL3 SDL3_image)

#target_compile_definitions(SDL3_image PRIVATE DAV1D_ASM=0)

add_subdirectory(src)

FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/assets")

file(GLOB ASSETS "assets/*")

file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR}/assets)

#configure_file(assets ${CMAKE_BINARY_DIR} COPYONLY)

# Now deal with potential libstdc++ problems on windows using mingw (if on msvc should be fine) (just use mscv)
if (MINGW)
    target_link_options(jump PRIVATE "-static-libstdc++" "-static-libgcc")
ENDIF()

target_link_libraries(jump PRIVATE
    SDL3::SDL3
        SDL3_image::SDL3_image
)