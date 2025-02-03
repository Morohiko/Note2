# Specify the path to googletest
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest
                 ${CMAKE_BINARY_DIR}/googletest_build
                 EXCLUDE_FROM_ALL)

# Now, link the test executable with gtest and gtest_main
add_executable(NoteTest
    parser_test.cpp
    encoder_test.cpp
    datetime_test.cpp
    note_test.cpp
    file_test.cpp
)

target_link_libraries(NoteTest
    gtest_main
    ${NOTE_LIB_NAME}
)

# Include the gtest headers
target_include_directories(NoteTest PRIVATE
    ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR}
)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(NoteTest)

