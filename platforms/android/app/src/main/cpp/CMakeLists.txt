# File: app/src/main/cpp/CMakeLists.txt

# Set the minimum version of CMake required.
cmake_minimum_required(VERSION 3.1.0)

# Define the project name.
project("note_andr_lib")

# Add the native library. The library name here must match the one you load in Java (System.loadLibrary("native-lib")).
add_library(
        note_andr_lib           # Library name.
        SHARED               # Build as a shared library.
        note_andr_lib.cpp       # Source file.
)

# Find libraries included in the NDK (e.g., log).
find_library(
        log-lib              # Variable to store the log library.
        log                  # Name of the log library.
)

# TODO: fix the path to the note_lib library.
set(NOTE_LIB_PATH ${CMAKE_SOURCE_DIR}/../../../../../../source)
add_subdirectory(${NOTE_LIB_PATH} note_lib)
include_directories(${NOTE_LIB_PATH})

# Link the log library to native-lib.
target_link_libraries(
        note_andr_lib
        ${log-lib}
        note_lib
)
