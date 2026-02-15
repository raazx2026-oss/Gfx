cmake_minimum_required(VERSION 3.10)
project(gfxlib)

set(CMAKE_CXX_STANDARD 11)

# Find JNI
find_package(JNI REQUIRED)

# Include current directory for headers
include_directories(${JNI_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# All .cpp files in the root
file(GLOB LIB_SOURCES "*.cpp")

# Build shared library
add_library(gfx SHARED ${LIB_SOURCES})

# Link Android log library
target_link_libraries(gfx log)