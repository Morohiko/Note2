#include <iostream>
#include <ctime>

#include "datetime.h"
#include "config.h"

int testCurrentDateDateTimeString() {
    std::wstring text;
    DateTime datetime;
    int retval;

    datetime.updateToCurrentDateTime();

    retval = datetime.getCurrentDateString(text);
    if (retval != STATUS_SUCCESS || text.length() != SIZE_OF_DATE) {
        return STATUS_TEST_FAILED;
    }

    retval = datetime.getCurrentDateTimeString(text);
    std::wcout << "getCurrentDateTimeString: text = " << text << std::endl;

    if (retval != STATUS_SUCCESS || text.length() != SIZE_OF_DATETIME) {
        return STATUS_TEST_FAILED;
    }
    return STATUS_SUCCESS;
}

int testCustomDateDateTimeString() {
    std::wstring date, expected_date;
    DateTime datetime;
    tm tm;
    int retval;

    tm.tm_year = 2022;
    tm.tm_mon = 3;
    tm.tm_mday = 2;
    tm.tm_hour = 12;
    tm.tm_min = 44;

    datetime.updateToCustomDateTime(tm);

    expected_date = L"2022/03/02";
    retval = datetime.getCurrentDateString(date);
    if (retval != STATUS_SUCCESS ||
        date.length() != SIZE_OF_DATE ||
        date.compare(expected_date) != 0) {
        return STATUS_TEST_FAILED;
    }

    expected_date = L"2022/03/02.12:44";
    retval = datetime.getCurrentDateTimeString(date);
    if (retval != STATUS_SUCCESS ||
        date.length() != SIZE_OF_DATETIME ||
        date.compare(expected_date) != 0) {
        return STATUS_TEST_FAILED;
    }
    return STATUS_SUCCESS;
}

int main() {
    int retval = STATUS_SUCCESS;
    bool isPassed = true;

    retval = testCurrentDateDateTimeString();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "datetime_test: testCurrentDateDateTimeString failed" << std::endl;
        isPassed = false;
    }

    retval = testCustomDateDateTimeString();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "datetime_test: testCustomDateDateTimeString failed" << std::endl;
        isPassed = false;
    }

    std::wcout << "datetime_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
    return (isPassed) ? STATUS_SUCCESS : STATUS_FAILURE;
}