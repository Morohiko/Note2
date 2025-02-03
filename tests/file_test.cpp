#include <gtest/gtest.h>
#include <fstream>

// grab the private members of the class
#define private public
#include "file.h"
#undef private
#include "config.h"

class FileTest : public ::testing::Test {
protected:
    File file;
    std::string testFilePath = "test.txt";
    
    void SetUp() override {
        // Create test file
        std::ofstream outFile(testFilePath);
        outFile.close();
    }

    void TearDown() override {
        // Clean up test file
        std::remove(testFilePath.c_str());
    }
};

TEST_F(FileTest, IsEmptyFile) {
    file.setPathToFile(testFilePath);
    EXPECT_TRUE(file.isCurrentFileEmpty());

    std::ofstream outFile(testFilePath);
    outFile << "test";
    outFile.close();
    
    EXPECT_FALSE(file.isCurrentFileEmpty());
}

TEST_F(FileTest, FileExists) {
    EXPECT_EQ(file.isFileExists(testFilePath), STATUS_SUCCESS);
    EXPECT_EQ(file.isFileExists("nonexistent.txt"), STATUS_FILE_NOT_FOUND);
}

TEST_F(FileTest, SetPathToFile) {
    EXPECT_EQ(file.setPathToFile(testFilePath), STATUS_SUCCESS);
    EXPECT_EQ(file.path, testFilePath);
    
    std::string nonexistentPath = "nonexistent.txt";
    EXPECT_EQ(file.setPathToFile(nonexistentPath), STATUS_FILE_NOT_FOUND);
}

// TODO: Fix this test
#if 0
TEST_F(FileTest, WriteToEndFile) {
    file.setPathToFile(testFilePath);
    
    std::wstring testData = L"Test data";
    EXPECT_EQ(file.writeToEndFile(testData), STATUS_SUCCESS);
    
    // Verify file contents
    std::wifstream inFile(testFilePath);
    std::wstring fileContent;
    std::getline(inFile, fileContent);
    EXPECT_EQ(fileContent, testData);
    inFile.close();
}
#endif

TEST_F(FileTest, ReadFromFileByPosition) {
    file.setPathToFile(testFilePath);
    
    // Write test data
    std::wstring testData = L"Hello World";
    file.writeToEndFile(testData);
    
    // Read and verify
    std::wstring output;
    int pos = 0;
    EXPECT_EQ(file.readFromFileByPosition(pos, 5, output), STATUS_SUCCESS);
    EXPECT_EQ(output.substr(0,5), L"Hello");
    
    pos = 6;
    EXPECT_EQ(file.readFromFileByPosition(pos, 5, output), STATUS_SUCCESS);
    EXPECT_EQ(output.substr(0,5), L"World");
}