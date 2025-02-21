cmake_minimum_required(VERSION 3.1.0)

set(NOTE_LIB_NAME "note_lib")

project(${NOTE_LIB_NAME} VERSION 1.0.0 LANGUAGES CXX)

add_library(${NOTE_LIB_NAME}
            parser.cpp
            file.cpp
            note.cpp
            encoder.cpp
            datetime.cpp
)
