#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"
#include "config.h"

int testGenerateStringFromSize() {
    Parser parser;
    std::wstring data, expectedData;
    int retval;

    expectedData = L"000010";
    retval = parser.generateStringFromSize(10, data);
    if (retval != STATUS_SUCCESS) {
        return STATUS_FAILURE;
    }
    if (expectedData.compare(data) != 0) return STATUS_TEST_FAILED;

    return STATUS_SUCCESS;
}

int testGenerateHead() {
    Parser parser;
    std::wstring data, datetime, expectedData;
    int size;
    int retval;

    datetime = L"2022/02/19.23:32";
    size = 30;
    expectedData = L"2022/02/19.23:32_000030_";

    retval = parser.generateHead(datetime, size, data);
    if (retval != STATUS_SUCCESS) {
        return STATUS_TEST_FAILED;
    }
    if (expectedData.compare(data) != 0) return STATUS_TEST_FAILED;

    return STATUS_SUCCESS;
}

int testParseHeadFromStringGetSize() {
    Parser parser;
    std::wstring text;
    int data, expectedData, retval;

    expectedData = 30;
    text = L"2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_SUCCESS || data != expectedData) {
        return STATUS_TEST_FAILED;
    }

    expectedData = 30;
    text = L"2022/02/19.23:32_000030_123123";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_SUCCESS || data != expectedData) {
        return STATUS_TEST_FAILED;
    }

    text = L"2022/02/19.23:32_00003";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_FAILURE) {
        return STATUS_TEST_FAILED;
    }

    text = L"2022/02/19.23:32_0000aa";
    retval = parser.parseHeadFromStringGetSize(text, data);
    if (retval != STATUS_FAILURE) {
        return STATUS_TEST_FAILED;
    }

    return STATUS_SUCCESS;
}

int testParseHeadFromStringGetTimeString() {
    Parser parser;
    std::wstring text, result, expectedData;
    int data, retval;

    expectedData = L"23:32";
    text = L"2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromStringGetTimeString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expectedData) != 0) {
        return STATUS_TEST_FAILED;
    }

    expectedData = L"23:32";
    text = L"2022/02/19.23:32";
    retval = parser.parseHeadFromStringGetTimeString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expectedData) != 0) {
        return STATUS_TEST_FAILED;
    }
    return STATUS_SUCCESS;
}

int testParseHeadFromStringGetDateString() {
    Parser parser;
    std::wstring text, result, expectedData;
    int data, retval;

    expectedData = L"2022/02/19";
    text = L"2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromStringGetDateString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expectedData) != 0) {
        return STATUS_TEST_FAILED;
    }

    expectedData = L"2022/02/19";
    text = L"2022/02/19.23:32";
    retval = parser.parseHeadFromStringGetDateString(text, result);
    if (retval != STATUS_SUCCESS || result.compare(expectedData) != 0) {
        return STATUS_TEST_FAILED;
    }
    return STATUS_SUCCESS;
}

int testParseHeadFromString() {

    Parser parser;
    std::wstring dateResult, expectedDate, text;
    int retval, sizeResult, expectedSize;

    expectedDate = L"2022/02/19";
    expectedSize = 30;
    text = L"2022/02/19.23:32_000030_";
    retval = parser.parseHeadFromString(text, dateResult, sizeResult);
    std::wcout << "text = " << text << ", dateResult = " << dateResult << ", sizeResult = " << sizeResult << std::endl;
    // if (retval != STATUS_SUCCESS || result.compare(expectedData) != 0) {
    //     return STATUS_TEST_FAILED;
    // }
    return STATUS_SUCCESS;
}

int main() {
    int retval;
    bool isPassed = true;
    retval = testGenerateStringFromSize();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "parser_test: testGenerateStringFromSize failed" << std::endl;
        isPassed = false;
    }
    retval = testGenerateHead();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "parser_test: testGenerateHead failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromStringGetSize();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "parser_test: testParseHeadFromStringGetSize failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromStringGetTimeString();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "parser_test: testParseHeadFromStringGetTimeString failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromStringGetDateString();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "parser_test: testParseHeadFromStringGetDateString failed" << std::endl;
        isPassed = false;
    }
    retval = testParseHeadFromString();
    if (retval != STATUS_SUCCESS) {
        std::wcout << "parser_test: testParseHeadFromString failed" << std::endl;
        isPassed = false;
    }

    std::wcout << "parser_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
    return (isPassed) ? STATUS_SUCCESS : STATUS_FAILURE;
}