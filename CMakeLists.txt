cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME "note2")
set(NOTE_LIB_NAME "note_lib")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLATFORM "linux" CACHE STRING "Platform for build (linux)")
option(WITH_TESTS "build tests" OFF)

# build note_lib
include_directories(source)

add_library(${NOTE_LIB_NAME}
            source/parser.cpp
            source/file.cpp
            source/note.cpp
            source/encoder.cpp
            source/datetime.cpp
)

# build bin for target
if (${PLATFORM} STREQUAL "linux")
    add_definitions(-DUSE_QT)

    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    include_directories(platforms/qt)
    add_executable(${PROJECT_NAME}
                    platforms/qt/main.cpp
                    platforms/qt/mainwindow.cpp
                    platforms/qt/treeitem.cpp)

    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core)
    target_link_libraries(${NOTE_LIB_NAME} Qt5::Core)

elseif(${PLATFORM} STREQUAL "dummy")
    add_definitions(-DUSE_DUMMY)
    include_directories(platforms/dummy)
    add_executable(${PROJECT_NAME}
                    platforms/dummy/main.cpp
                    platforms/dummy/dummy.cpp)
else()
    message(FATAL_ERROR "platform is not supported, please use linux, dummy")
endif()

message("PLATFORM: " ${PLATFORM})

target_link_libraries(${PROJECT_NAME} ${NOTE_LIB_NAME})

if (${WITH_TESTS})
    set(PARSER_TEST_NAME "parser_test")
    add_executable(${PARSER_TEST_NAME} test/parser_test/main.cpp)
    target_link_libraries(${PARSER_TEST_NAME} ${NOTE_LIB_NAME})

    set(DATETIME_TEST_NAME "datetime_test")
    add_executable(${DATETIME_TEST_NAME} test/datetime_test/main.cpp)
    target_link_libraries(${DATETIME_TEST_NAME} ${NOTE_LIB_NAME})

    set(FILE_TEST_NAME "file_test")
    add_executable(${FILE_TEST_NAME} test/file_test/main.cpp)
    target_link_libraries(${FILE_TEST_NAME} ${NOTE_LIB_NAME})

    set(LOGGER_TEST_NAME "logger_test")
    add_executable(${LOGGER_TEST_NAME} test/logger_test/main.cpp)
    target_link_libraries(${LOGGER_TEST_NAME} ${NOTE_LIB_NAME})

    if (${PLATFORM} STREQUAL "dummy")
        set(DUMMY_TEST_NAME "dummy_test")
        add_executable(${DUMMY_TEST_NAME} platforms/dummy/dummy.cpp test/dummy_test/main.cpp)
        target_link_libraries(${DUMMY_TEST_NAME} ${NOTE_LIB_NAME})
    endif()
endif()
