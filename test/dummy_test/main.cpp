#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <fstream>

#include "dummy.h"
#include "note.h"
#include "config.h"

int testSetFilenameHandler(Dummy &dummy) {
    int retval = STATUS_SUCCESS;
    std::string filename = "filename.txt";
    // file is not exist case
    retval = dummy.setFilenameHandler(&filename);
    if (retval != STATUS_FILE_NOT_FOUND) {
        return STATUS_TEST_FAILED;
    }

    // file is exist case
    std::wofstream MyFile(filename.c_str());
    MyFile.close();
    retval = dummy.setFilenameHandler(&filename);
    std::remove(filename.c_str());
    if (retval != STATUS_SUCCESS) {
        return STATUS_TEST_FAILED;
    }

    return STATUS_SUCCESS;
}

int testPerformReadByDateHandler(Dummy &dummy) {
    int retval = STATUS_SUCCESS;
    std::wstring text, expected_text;
    std::string filename = "filename.txt";

    std::wofstream MyFile(filename.c_str());
    MyFile << L"2022/02/19.23:32_000030_123123_";
    MyFile.close();
    retval = dummy.setFilenameHandler(&filename);
    if (retval != STATUS_SUCCESS) {
        return STATUS_TEST_FAILED;
    }
    tm tm;
    tm.tm_year = 2022;
    tm.tm_mon = 2;
    tm.tm_mday = 19;
    std::wstring key;
    retval = dummy.performReadByDateHandler(&tm, &text, &key);
    expected_text = L"23:32\n123123\n\n";
    if (expected_text.compare(text) != 0) {
        return STATUS_TEST_FAILED;
    }
    return retval;
}

int testPerformReadAllDateHandle(Dummy &dummy) {
    int retval = STATUS_SUCCESS;
    std::string filename = "filename.txt";
    std::wofstream MyFile(filename.c_str());
    MyFile << L"2022/02/19.23:32_000030_1231232010/01/01.01:01_000030_222222";
    MyFile.close();
    retval = dummy.setFilenameHandler(&filename);
    if (retval != STATUS_SUCCESS) {
        return STATUS_TEST_FAILED;
    }
    std::list<std::wstring> expectedList;
    expectedList.push_back(L"2022/02/19");
    expectedList.push_back(L"2020/03/24");
    std::list<std::wstring> dateList;
    std::wstring key;
    retval = dummy.performReadAllDateHandler(&dateList, &key);
    if (retval != 2) {
        std::wcout << LOG_ERROR << "return must be count of read data" << std::endl;
        return STATUS_TEST_FAILED;
    }
    if (expectedList.size() != dateList.size()) {
        std::wcout << LOG_ERROR << "size missmatch" << std::endl;
        return STATUS_TEST_FAILED;
    }
    std::list<std::wstring>::iterator itDateList = dateList.begin();
    std::list<std::wstring>::iterator itExpectedList = expectedList.begin();
    for (int i = 0; i < dateList.size(); i++) {
        std::advance(itDateList, i);
        std::advance(itExpectedList, i);
        if (itExpectedList->compare(*itExpectedList) != 0) {
            std::wcout << LOG_ERROR << "date missmatch: " << *itDateList << " != " << *itExpectedList << std::endl;
            return STATUS_TEST_FAILED;
        }
    }
    return STATUS_SUCCESS;
}

int main() {
    Note note;
    Dummy dummy;
    int retval;
    bool isPassed = true;

    dummy.setCallbacks(Note::setFilenameHandler, Note::performReadByDateHandler,
                       Note::performReadAllDateHandler, Note::performWriteToFileHandler);

    retval = testSetFilenameHandler(dummy);
    if (retval != STATUS_SUCCESS) {
        std::wcout << "dummy_test: testSetFilenameHandler failed" << std::endl;
        isPassed = false;
    }
    std::wcout << LOG_DEBUG << "==================== testPerformReadByDateHandler ================" << std::endl;
    retval = testPerformReadByDateHandler(dummy);
    if (retval != STATUS_SUCCESS) {
        std::wcout << "dummy_test: testPerformReadByDateHandler failed" << std::endl;
        isPassed = false;
    }
    retval = testPerformReadAllDateHandle(dummy);
    if (retval != STATUS_SUCCESS) {
        std::wcout << "dummy_test: testPerformReadAllDateHandle failed" << std::endl;
        isPassed = false;
    }
    std::wcout << "dummy_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
    return (isPassed) ? STATUS_SUCCESS : STATUS_FAILURE;
}