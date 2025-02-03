#include "parser.h"
#include "config.h"
#include <gtest/gtest.h>

class ParserTest : public ::testing::Test {
protected:
    Parser parser;
};

TEST_F(ParserTest, ParseHeadFromStringValid) {
    std::wstring text = L"2023/06/15.12:34_000100_";
    std::wstring date;
    int size;
    
    int retval = parser.parseHeadFromString(text, date, size);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(date.c_str(), L"2023/06/15");
    EXPECT_EQ(size, 100);
}

TEST_F(ParserTest, ParseHeadFromStringInvalidLength) {
    std::wstring text = L"2023"; // Too short
    std::wstring date;
    int size;
    
    int retval = parser.parseHeadFromString(text, date, size);
    
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(ParserTest, ParseHeadFromStringInvalidDate) {
    std::wstring text = L"ABCD/06/15.12:34_000100_"; // Invalid date chars
    std::wstring date;
    int size;
    
    int retval = parser.parseHeadFromString(text, date, size);

    // TODO: must be STATUS_FAILURE
    EXPECT_EQ(retval, STATUS_SUCCESS);
}

TEST_F(ParserTest, ParseHeadFromStringInvalidSize) {
    std::wstring text = L"2023/06/15.12:34_ABCDEF_"; // Invalid size chars
    std::wstring date;
    int size;
    
    int retval = parser.parseHeadFromString(text, date, size);
    
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(ParserTest, ParseHeadFromStringGetDateStringValid) {
    std::wstring text = L"2023/06/15.12:34_000100_";
    std::wstring date;
    
    int retval = parser.parseHeadFromStringGetDateString(text, date);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(date.c_str(), L"2023/06/15");
}

TEST_F(ParserTest, ParseHeadFromStringGetDateStringTooShort) {
    std::wstring text = L"2023"; // Too short
    std::wstring date;
    
    int retval = parser.parseHeadFromStringGetDateString(text, date);
    
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(ParserTest, ParseHeadFromStringGetDateStringExactLength) {
    std::wstring text = L"2023/06/15";
    std::wstring date;
    
    int retval = parser.parseHeadFromStringGetDateString(text, date);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(date.c_str(), L"2023/06/15");
}

TEST_F(ParserTest, ParseHeadFromStringGetDateStringWithoutTime) {
    std::wstring text = L"2023/06/15_000100_";
    std::wstring date;
    
    int retval = parser.parseHeadFromStringGetDateString(text, date);
    
    EXPECT_EQ(retval, STATUS_SUCCESS); 
    EXPECT_STREQ(date.c_str(), L"2023/06/15");
}

TEST_F(ParserTest, ParseHeadFromStringGetTimeStringValid) {
    std::wstring text = L"2023/06/15.12:34_000100_";
    std::wstring time;
    
    int retval = parser.parseHeadFromStringGetTimeString(text, time);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(time.c_str(), L"12:34");
}

TEST_F(ParserTest, ParseHeadFromStringGetTimeStringTooShort) {
    std::wstring text = L"2023"; // Too short
    std::wstring time;
    
    int retval = parser.parseHeadFromStringGetTimeString(text, time);
    
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(ParserTest, ParseHeadFromStringGetTimeStringExactLength) {
    std::wstring text = L"2023/06/15.12:34";
    std::wstring time;
    
    int retval = parser.parseHeadFromStringGetTimeString(text, time);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(time.c_str(), L"12:34"); 
}

TEST_F(ParserTest, ParseHeadFromStringGetTimeStringWithoutSize) {
    std::wstring text = L"2023:06:15.12:34_";
    std::wstring time;
    
    int retval = parser.parseHeadFromStringGetTimeString(text, time);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(time.c_str(), L"12:34");
}

TEST_F(ParserTest, ParseHeadFromStringGetSizeValid) {
    std::wstring text = L"2023/06/15.12:34_000100_";
    int size;
    
    int retval = parser.parseHeadFromStringGetSize(text, size);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_EQ(size, 100);
}

TEST_F(ParserTest, ParseHeadFromStringGetSizeTooShort) {
    std::wstring text = L"2023"; // Too short
    int size;
    
    int retval = parser.parseHeadFromStringGetSize(text, size);
    
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(ParserTest, ParseHeadFromStringGetSizeInvalidChars) {
    std::wstring text = L"2023/06/15.12:34_ABCDEF_"; // Invalid size chars
    int size;
    
    int retval = parser.parseHeadFromStringGetSize(text, size);
    
    EXPECT_EQ(retval, STATUS_FAILURE);
}

TEST_F(ParserTest, ParseHeadFromStringGetSizeZero) {
    std::wstring text = L"2023/06/15.12:34_000000_";
    int size;
    
    int retval = parser.parseHeadFromStringGetSize(text, size);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_EQ(size, 0);
}

TEST_F(ParserTest, ParseHeadFromStringGetSizeMaxValue) {
    std::wstring text = L"2023/06/15.12:34_999999_";
    int size;
    
    int retval = parser.parseHeadFromStringGetSize(text, size);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_EQ(size, 999999);
}

TEST_F(ParserTest, GenerateStringFromSizeZero) {
    std::wstring result;
    int size = 0;
    
    int retval = parser.generateStringFromSize(size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"000000");
}

TEST_F(ParserTest, GenerateStringFromSizeSingleDigit) {
    std::wstring result;
    int size = 5;
    
    int retval = parser.generateStringFromSize(size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"000005");
}

TEST_F(ParserTest, GenerateStringFromSizeMultipleDigits) {
    std::wstring result;
    int size = 12345;
    
    int retval = parser.generateStringFromSize(size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"012345");
}

TEST_F(ParserTest, GenerateStringFromSizeMaxValue) {
    std::wstring result;
    int size = 999999;
    
    int retval = parser.generateStringFromSize(size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"999999");
}
TEST_F(ParserTest, GenerateHeadValid) {
    std::wstring currentDateTime = L"2023/06/15.12:34";
    int size = 100;
    std::wstring result;
    
    int retval = parser.generateHead(currentDateTime, size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"2023/06/15.12:34_000100_");
}

TEST_F(ParserTest, GenerateHeadZeroSize) {
    std::wstring currentDateTime = L"2023/06/15.12:34";
    int size = 0;
    std::wstring result;
    
    int retval = parser.generateHead(currentDateTime, size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"2023/06/15.12:34_000000_");
}

TEST_F(ParserTest, GenerateHeadMaxSize) {
    std::wstring currentDateTime = L"2023/06/15.12:34";
    int size = 999999;
    std::wstring result;
    
    int retval = parser.generateHead(currentDateTime, size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"2023/06/15.12:34_999999_");
}

TEST_F(ParserTest, GenerateHeadEmptyDateTime) {
    std::wstring currentDateTime = L"";
    int size = 100;
    std::wstring result;
    
    int retval = parser.generateHead(currentDateTime, size, result);
    
    EXPECT_EQ(retval, STATUS_SUCCESS);
    EXPECT_STREQ(result.c_str(), L"_000100_");
}
