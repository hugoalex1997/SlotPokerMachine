cmake_minimum_required(VERSION 3.10)

# set the project name
project(PokerSlot)

# Include cmake util functions
include(${CMAKE_SOURCE_DIR}/utils/cmake/utils.cmake)

# Downloads SFML library
downloadSFML()

set(SFML_DIR "external/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
        )

include_directories(src)

# add the executable
add_executable(PokerSlot ${SOURCES})

target_link_libraries(PokerSlot sfml-graphics sfml-audio sfml-system sfml-window)