#include <iostream>
#include <fstream>
#include <string>

#include "file.h"
#include "config.h"
#include "log.h"

#define PATH_FILE "/home/user/work/Note2/test/file_test/testfile.txt"

// **************** help functions ******************* //
bool isFileExists(std::string &name) {
    std::wifstream f(name.c_str());
    return f.good();
}

int createFile(std::string &name) {
    std::wofstream MyFile(name);
    MyFile.close();
    return STATUS_SUCCESS;
}

// *************************************************** //

int testWriteReadFile(std::string &filepath) {
    if (isFileExists(filepath)) {
        std::remove(filepath.c_str());
    }
    createFile(filepath);

    File file;
    file.setPathToFile(filepath);
    std::wstring test_text = L"test_text";
    file.writeToEndFile(test_text);
    file.writeToEndFile(test_text);
    for (int i = 0; i < 40; i+=5) {
        std::wstring output;
        int retval = file.readFromFileByPosition(i, 5, output);
        WLOG(LOG_INFO, "output = ", output, ", retval = ", retval);
    }
    return STATUS_SUCCESS;
}

int main() {
    std::string filepath = "testfile.txt";
    int retval;
    bool isPassed = true;

    retval = testWriteReadFile(filepath);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_INFO, "file_test: testWriteReadFile failed");
        isPassed = false;
    }

    WLOG(LOG_INFO, "file_test: done ", ((isPassed) ? "passed" : "failed"));
    return (isPassed) ? STATUS_SUCCESS : STATUS_FAILURE;
}