cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME "note2")
set(PLATFORM_NAME "platform")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLATFORM "linux" CACHE STRING "Platform for build (linux)")

if (${PLATFORM} STREQUAL "linux")
    message("PLATFORM: " ${PLATFORM})

    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    include_directories(platforms/qt)
    add_library(${PLATFORM_NAME}
                    platforms/qt/mainwindow.cpp
                    platforms/qt/treeitem.cpp)

    target_link_libraries(${PLATFORM_NAME} Qt5::Widgets Qt5::Core)
else()
    message(FATAL_ERROR "platform is not supported")
endif()

include_directories(source)

add_executable(${PROJECT_NAME}
    source/parser.cpp
    source/file.cpp
    source/main.cpp
    source/note.cpp
    source/utils.cpp
    source/timesheet.cpp
    source/encoder.cpp
)

target_link_libraries(${PROJECT_NAME} ${PLATFORM_NAME})
