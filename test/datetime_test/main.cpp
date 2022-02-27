#include <iostream>
#include <ctime>

#include "datetime.h"
#include "config.h"

int testCurrentDateDateTimeString() {
    std::string text;
    DateTime datetime;

    datetime.updateToCurrentDateTime();

    text = datetime.getCurrentDateString();
    if (text.length() != SIZE_OF_DATE) {
        return STATUS_TEST_FAILED;
    }

    text = datetime.getCurrentDateTimeString();
    std::cout << "getCurrentDateTimeString: text = " << text << std::endl;

    if (text.length() != SIZE_OF_DATETIME) {
        return STATUS_TEST_FAILED;
    }
    return STATUS_SUCCESS;
}

int testCustomDateDateTimeString() {
    std::string date, expected_date;
    DateTime datetime;
    tm tm;
    tm.tm_year = 2022;
    tm.tm_mon = 3;
    tm.tm_mday = 2;
    tm.tm_hour = 12;
    tm.tm_min = 44;

    datetime.updateToCustomDateTime(&tm);

    expected_date = "2022/03/02";
    date = datetime.getCurrentDateString();
    if (date.length() != SIZE_OF_DATE ||
        date.compare(expected_date) != 0) {
        return STATUS_TEST_FAILED;
    }

    expected_date = "2022/03/02.12:44";
    date = datetime.getCurrentDateTimeString();
    if (date.length() != SIZE_OF_DATETIME ||
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
        std::cout << "datetime_test: testCurrentDateDateTimeString failed" << std::endl;
        isPassed = false;
    }

    retval = testCustomDateDateTimeString();
    if (retval != STATUS_SUCCESS) {
        std::cout << "datetime_test: testCurrentDateDateTimeString failed" << std::endl;
        isPassed = false;
    }

    std::cout << "datetime_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
    return 0;
}