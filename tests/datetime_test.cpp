#include <gtest/gtest.h>
#include "datetime.h"

class DateTimeTest : public ::testing::Test {
protected:
    DateTime dateTime;
};

TEST_F(DateTimeTest, GetCurrentDateString) {
    std::wstring date;
    dateTime.getCurrentDateString(date);
    
    // Check format yyyy/MM/dd
    EXPECT_EQ(date.length(), 10);
    EXPECT_EQ(date[4], L'/');
    EXPECT_EQ(date[7], L'/');
}

TEST_F(DateTimeTest, GetCurrentDateTimeString) {
    std::wstring dt;
    dateTime.getCurrentDateTimeString(dt);
    
    // Check format yyyy/MM/dd.hh:mm
    EXPECT_EQ(dt.length(), 16);
    EXPECT_EQ(dt[4], L'/');
    EXPECT_EQ(dt[7], L'/');
    EXPECT_EQ(dt[10], L'.');
    EXPECT_EQ(dt[13], L':');
}

TEST_F(DateTimeTest, CustomDateTime) {
    tm custom_time = {};
    custom_time.tm_year = 2023;
    custom_time.tm_mon = 12;
    custom_time.tm_mday = 25;
    custom_time.tm_hour = 13;
    custom_time.tm_min = 45;
    
    dateTime.updateToCustomDateTime(custom_time);
    
    std::wstring date;
    dateTime.getCurrentDateString(date);
    EXPECT_EQ(date, L"2023/12/25");
    
    std::wstring datetime;
    dateTime.getCurrentDateTimeString(datetime);
    EXPECT_EQ(datetime, L"2023/12/25.13:45");
}

TEST_F(DateTimeTest, ConvertTmDateToString) {
    tm test_time = {};
    test_time.tm_year = 2024;
    test_time.tm_mon = 1;
    test_time.tm_mday = 1;
    
    std::wstring result;
    dateTime.convertTmDateToString(test_time, result);
    EXPECT_EQ(result, L"2024/01/01");
}

TEST_F(DateTimeTest, PaddingZeros) {
    tm test_time = {};
    test_time.tm_year = 999; // Should pad to 0999
    test_time.tm_mon = 1;    // Should pad to 01
    test_time.tm_mday = 2;   // Should pad to 02
    
    std::wstring result;
    dateTime.convertTmDateToString(test_time, result);
    EXPECT_EQ(result, L"0999/01/02");
}