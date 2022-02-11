cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME "note2")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(win/note2/)
add_executable(${PROJECT_NAME}
    win/note2/parser.cpp
    win/note2/interface/mainwindow.cpp
    win/note2/interface/treeitem.cpp
    win/note2/file.cpp
    win/note2/main.cpp
    win/note2/note.cpp
    win/note2/utils.cpp
    win/note2/timesheet.cpp
    win/note2/encoder.cpp
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core)