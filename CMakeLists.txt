cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME "note2")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLATFORM "linux" CACHE STRING "Platform for build (linux)")
option(WITH_TESTS "build tests" ON)

# build note_lib
include_directories(source)
add_subdirectory(source)

# build bin for target
if (${PLATFORM} STREQUAL "linux")
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    include_directories(platforms/qt)
    add_executable(${PROJECT_NAME}
                    platforms/qt/main.cpp
                    platforms/qt/mainwindow.cpp
                    platforms/qt/treeitem.cpp)

    target_link_libraries(${NOTE_LIB_NAME} Qt5::Core)
    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core note_lib)

elseif(${PLATFORM} STREQUAL "dummy")
    include_directories(platforms/dummy)
    add_executable(${PROJECT_NAME}
                    platforms/dummy/main.cpp)
    target_link_libraries(${PROJECT_NAME} note_lib)

elseif(${PLATFORM} STREQUAL "android")
    add_custom_target(run ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Running build_and_install.sh..."
        COMMAND ${CMAKE_SOURCE_DIR}/platforms/android/build_install.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/platforms/android
        COMMENT "Building app and installing to connected device"
        VERBATIM
    )
elseif(${PLATFORM} STREQUAL "cli")
    find_path(FTXUI_INCLUDE_DIR NAMES ftxui/component/component.hpp)
    include_directories(${FTXUI_INCLUDE_DIR})

    find_library(FTXUI_LIB_COMPONENT NAMES ftxui-component)
    find_library(FTXUI_LIB_DOM NAMES ftxui-dom)
    find_library(FTXUI_LIB_SCREEN NAMES ftxui-screen)

    include_directories(platforms/cli)
    add_executable(${PROJECT_NAME}
                    platforms/cli/cli.cpp
                    platforms/cli/main.cpp)

    find_package(Threads REQUIRED)

    target_link_libraries(${PROJECT_NAME} note_lib)
    target_link_libraries(${PROJECT_NAME} ${FTXUI_LIB_COMPONENT} ${FTXUI_LIB_DOM} ${FTXUI_LIB_SCREEN} Threads::Threads)    
else()
    message(FATAL_ERROR "platform is not supported")
endif()

message("PLATFORM: " ${PLATFORM})


if (${WITH_TESTS})
    # gtest
    enable_testing()
    add_subdirectory(tests)
endif()
