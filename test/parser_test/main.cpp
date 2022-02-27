#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"
#include "config.h"

int testGenerateStringFromSize() {
    Parser parser;
    std::string data, expected_data;

    expected_data = "000010";
    data = parser.generateStringFromSize(10);

    if (expected_data.compare(data) != 0) return STATUS_TEST_FAILED;

    return STATUS_SUCCESS;
}

int testGenerateHead() {
    Parser parser;
    std::string data, datetime, expected_data;
    int size;

    datetime = "2022/02/19.23:32";
    size = 30;
    expected_data = "2022/02/19.23:32_000030_";

    data = parser.generateHead(datetime, size);
    if (expected_data.compare(data) != 0) return STATUS_TEST_FAILED;

    return STATUS_SUCCESS;
}

int testParseHeadFromStringGetSize() {
    Parser parser;
    std::string text;
    int data, expected_data, retval;

    expected_data = 30;
    text = "2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_SUCCESS || data != expected_data) {
        return STATUS_TEST_FAILED;
    }

    expected_data = 30;
    text = "2022/02/19.23:32_000030_123123";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_SUCCESS || data != expected_data) {
        return STATUS_TEST_FAILED;
    }

    text = "2022/02/19.23:32_00003";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_FAILURE) {
        return STATUS_TEST_FAILED;
    }

    text = "2022/02/19.23:32_0000aa";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_FAILURE) {
        return STATUS_TEST_FAILED;
    }

    return STATUS_SUCCESS;
}

int testParseHeadFromStringGetTimeString() {
    Parser parser;
    std::string text, result, expected_data;
    int data, retval;

    expected_data = "23:32";
    text = "2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromStringGetTimeString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expected_data) != 0) {
        return STATUS_TEST_FAILED;
    }

    expected_data = "23:32";
    text = "2022/02/19.23:32";
    retval = parser.parseHeadFromStringGetTimeString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expected_data) != 0) {
        return STATUS_TEST_FAILED;
    }
    return STATUS_SUCCESS;
}

int testParseHeadFromStringGetDateString() {
    Parser parser;
    std::string text, result, expected_data;
    int data, retval;

    expected_data = "2022/02/19";
    text = "2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromStringGetDateString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expected_data) != 0) {
        return STATUS_TEST_FAILED;
    }

    expected_data = "2022/02/19";
    text = "2022/02/19.23:32";
    retval = parser.parseHeadFromStringGetDateString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expected_data) != 0) {
        return STATUS_TEST_FAILED;
    }
    return STATUS_SUCCESS;
}

int testParseHeadFromString() {

    Parser parser;
    std::string dateResult, expectedDate, text;
    int retval, sizeResult, expectedSize;

    expectedDate = "2022/02/19";
    expectedSize = 30;
    text = "2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromString(text, dateResult, sizeResult);
    std::cout << "text = " << text << ", dateResult = " << dateResult << ", sizeResult = " << sizeResult << std::endl;
    // if (retval != STATUS_SUCCESS || result.compare(expected_data) != 0) {
    //     return STATUS_TEST_FAILED;
    // }
    return STATUS_SUCCESS;
}

int main() {
    int retval;
    bool isPassed = true;
    retval = testGenerateStringFromSize();
    if (retval != STATUS_SUCCESS) {
        std::cout << "parser_test: testGenerateStringFromSize failed" << std::endl;
        isPassed = false;
    }
    retval = testGenerateHead();
    if (retval != STATUS_SUCCESS) {
        std::cout << "parser_test: testGenerateHead failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromStringGetSize();
    if (retval != STATUS_SUCCESS) {
        std::cout << "parser_test: testParseHeadFromStringGetSize failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromStringGetTimeString();
    if (retval != STATUS_SUCCESS) {
        std::cout << "parser_test: testParseHeadFromStringGetTimeString failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromStringGetDateString();
    if (retval != STATUS_SUCCESS) {
        std::cout << "parser_test: testParseHeadFromStringGetDateString failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromString();
    if (retval != STATUS_SUCCESS) {
        std::cout << "parser_test: testParseHeadFromString failed" << std::endl;
        isPassed = false;
    }

    std::cout << "parser_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
    return 0;
}