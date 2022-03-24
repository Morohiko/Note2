#include <iostream>
#include <ctime>

#include "datetime.h"
#include "config.h"
#include "log.h"

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
    WLOG(LOG_INFO, "getCurrentDateTimeString: text = ", text);

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
        WLOG(LOG_INFO, "datetime_test: testCurrentDateDateTimeString failed");
        isPassed = false;
    }

    retval = testCustomDateDateTimeString();
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_INFO, "datetime_test: testCustomDateDateTimeString failed");
        isPassed = false;
    }

    WLOG(LOG_INFO, "datetime_test: done ", ((isPassed) ? "passed" : "failed"));
    return (isPassed) ? STATUS_SUCCESS : STATUS_FAILURE;
}