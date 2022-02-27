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

    retval = dummy.setFilenameHandler("somefile");
    if (retval != STATUS_FILE_NOT_FOUND) {
        return STATUS_TEST_FAILED;
    }

    std::ofstream MyFile("filename.txt");
    MyFile.close();
    retval = dummy.setFilenameHandler("filename.txt");
    std::remove("filename.txt");
    if (retval != STATUS_SUCCESS) {
        return STATUS_TEST_FAILED;
    }

    return STATUS_SUCCESS;
}

int testPerformReadByDateHandler(Dummy &dummy) {
    int retval = STATUS_SUCCESS;
    std::string text, expected_text;

    std::ofstream MyFile("filename.txt");
    MyFile << "2022/02/19.23:32_000030_123123";
    MyFile.close();
    retval = dummy.setFilenameHandler("filename.txt");
    if (retval != STATUS_SUCCESS) {
        return STATUS_TEST_FAILED;
    }
    tm tm;
    tm.tm_year = 2022;
    tm.tm_mon = 2;
    tm.tm_mday = 19;
    std::string key;
    retval = dummy.performReadByDateHandler(&tm, &text, &key);
    expected_text = "23:32\n123123\n\n";
    if (expected_text.compare(text) != 0) {
        return STATUS_TEST_FAILED;
    }
    return retval;
}

int testPerformReadAllDateHandle(Dummy &dummy) {
    int retval = STATUS_SUCCESS;
    std::ofstream MyFile("filename.txt");
    MyFile << "2022/02/19.23:32_000030_1231232010/01/01.01:01_000030_222222";
    MyFile.close();
    retval = dummy.setFilenameHandler("filename.txt");
    if (retval != STATUS_SUCCESS) {
        return STATUS_TEST_FAILED;
    }
    std::list<std::string> expectedList;
    expectedList.push_back("2022/02/19");
    expectedList.push_back("2020/03/24");
    std::list<std::string> dateList;
    std::string key;
    retval = dummy.performReadAllDateHandler(&dateList, &key);
    if (retval != 2) {
        std::cout << "return must be count of read data" << std::endl;
        return STATUS_TEST_FAILED;
    }
    if (expectedList.size() != dateList.size()) {
        std::cout << LOG_ERROR << "size missmatch" << std::endl;
        return STATUS_TEST_FAILED;
    }
    std::list<std::string>::iterator itDateList = dateList.begin();
    std::list<std::string>::iterator itExpectedList = expectedList.begin();
    for (int i = 0; i < dateList.size(); i++) {
        std::advance(itDateList, i);
        std::advance(itExpectedList, i);
        if (itExpectedList->compare(*itExpectedList) != 0) {
            std::cout << LOG_ERROR << "date missmatch: " << *itDateList << " != " << *itExpectedList << std::endl;
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
        std::cout << "dummy_test: testSetFilenameHandler failed" << std::endl;
        isPassed = false;
    }
    std::cout << LOG_DEBUG << "==================== testPerformReadByDateHandler ================" << std::endl;
    retval = testPerformReadByDateHandler(dummy);
    if (retval != STATUS_SUCCESS) {
        std::cout << "dummy_test: testPerformReadByDateHandler failed" << std::endl;
        isPassed = false;
    }
    retval = testPerformReadAllDateHandle(dummy);
    if (retval != STATUS_SUCCESS) {
        std::cout << "dummy_test: testPerformReadAllDateHandle failed" << std::endl;
        isPassed = false;
    }
    std::cout << "dummy_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
    return 0;
}