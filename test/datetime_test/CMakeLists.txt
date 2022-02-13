cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME "datetime_test")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/home/user/work/Note2/source/)
add_executable(${PROJECT_NAME}
                main.cpp
                /home/user/work/Note2/source/datetime.cpp)
