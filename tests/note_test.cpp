#include <gtest/gtest.h>
#include <string>
#include <fstream>

// grab the private members of the class
#define private public
#include "note.h"
#undef private

class NoteTest : public ::testing::Test {
protected:
    Note note;
    
    void SetUp() override {
        // create test file
        std::ofstream file("test.txt");
        file.close();

        // Set up test file
        std::string filename = "test.txt";
        note.setFilename(filename);
    }

    void TearDown() override {
        // remove test file
        std::remove("test.txt");
    }
};

TEST_F(NoteTest, WriteToFileBasic) {
    std::wstring text = L"Test content";
    std::wstring key = L"testkey";
    tm datetime = {};
    datetime.tm_year = 2023;
    datetime.tm_mon = 6;
    datetime.tm_mday = 15;
    datetime.tm_hour = 12;
    datetime.tm_min = 34;

    int retval = note.performWriteToFile(text, true, datetime, key);
    EXPECT_EQ(retval, STATUS_SUCCESS);
}

TEST_F(NoteTest, WriteToFileEmptyText) {
    std::wstring text = L"";
    std::wstring key = L"testkey"; 
    tm datetime = {};
    datetime.tm_year = 2023;
    datetime.tm_mon = 6;
    datetime.tm_mday = 15;

    int retval = note.performWriteToFile(text, true, datetime, key);
    EXPECT_EQ(retval, STATUS_SUCCESS);
}

TEST_F(NoteTest, ReadByDateBasic) {
    tm date = {};
    date.tm_year = 2023;
    date.tm_mon = 6;
    date.tm_mday = 15;
    std::wstring key = L"testkey";
    std::wstring outputBody;

    int retval = note.performReadByDate(date, key, outputBody);
    EXPECT_EQ(retval, STATUS_SUCCESS);
}

TEST_F(NoteTest, ReadByDateInvalidDate) {
    tm date = {};
    date.tm_year = -1; // Invalid year
    std::wstring key = L"testkey";
    std::wstring outputBody;

    int retval = note.performReadByDate(date, key, outputBody); 
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(NoteTest, ReadAllDatesBasic) {
    std::wstring key = L"testkey";
    std::list<std::wstring> dateList;

    int retval = note.performReadAllDate(key, dateList);
    EXPECT_EQ(retval, STATUS_SUCCESS);
}

TEST_F(NoteTest, ReadEmptyFile) {
    std::wstring key = L"testkey";
    std::list<std::wstring> dateList;
    
    // Set empty file
    std::string emptyFile = "empty.txt";
    note.setFilename(emptyFile);

    int retval = note.performReadAllDate(key, dateList);
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_TRUE(dateList.empty());
}

TEST_F(NoteTest, SetInvalidFilename) {
    std::string invalidFile = "/invalid/path/file.txt";
    int retval = note.setFilename(invalidFile);
    EXPECT_EQ(retval, STATUS_FILE_NOT_FOUND);
}

TEST_F(NoteTest, WriteWithEmptyKey) {
    std::wstring text = L"Test content";
    std::wstring emptyKey = L"";
    tm datetime = {};
    
    int retval = note.performWriteToFile(text, false, datetime, emptyKey);
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(NoteTest, ReadAllWithEmptyKey) {
    std::wstring emptyKey = L"";
    std::list<std::wstring> dateList;

    int retval = note.performReadAllDate(emptyKey, dateList);
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(NoteTest, WriteAndReadBack) {
    std::wstring text = L"Test content";
    std::wstring key = L"testkey";
    tm datetime = {};
    datetime.tm_year = 2023;
    datetime.tm_mon = 6;
    datetime.tm_mday = 15;

    // Write
    int retval = note.performWriteToFile(text, true, datetime, key);
    EXPECT_EQ(retval, STATUS_SUCCESS);

    // Read back
    std::wstring outputBody;
    retval = note.performReadByDate(datetime, key, outputBody);
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_TRUE(outputBody.find(text) != std::wstring::npos);
}
