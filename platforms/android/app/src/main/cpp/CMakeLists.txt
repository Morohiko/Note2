# File: app/src/main/cpp/CMakeLists.txt

# Set the minimum version of CMake required.
cmake_minimum_required(VERSION 3.10.2)

# Define the project name.
project("note2_lib")

# Add the native library. The library name here must match the one you load in Java (System.loadLibrary("native-lib")).
add_library(
        note2_lib           # Library name.
        SHARED               # Build as a shared library.
        note2_lib.cpp       # Source file.
)

# Find libraries included in the NDK (e.g., log).
find_library(
        log-lib              # Variable to store the log library.
        log                  # Name of the log library.
)

# Link the log library to native-lib.
target_link_libraries(
        note2_lib
        ${log-lib}
)
