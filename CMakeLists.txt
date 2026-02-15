cmake_minimum_required(VERSION 3.10)
project(gfxlib)

set(CMAKE_CXX_STANDARD 11)

# Find JNI
find_package(JNI REQUIRED)

# Include directories
include_directories(${JNI_INCLUDE_DIRS})
include_directories(src/main/cpp)

# Source files
file(GLOB LIB_SOURCES "src/main/cpp/*.cpp")

# Create shared library
add_library(gfx SHARED ${LIB_SOURCES})

# Link libraries
target_link_libraries(gfx log)