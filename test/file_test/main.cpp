#include <iostream>
#include <fstream>
#include <string>

#include "file.h"
#include "config.h"

#define PATH_FILE "/home/user/work/Note2/test/file_test/testfile.txt"

// **************** help functions ******************* //
bool isFileExists(std::string &name) {
    std::wifstream f(name.c_str());
    return f.good();
}

int createFile(std::string &name) {
    std::wofstream MyFile(name);
    MyFile.close();
    return 0;
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
        std::wcout << "output = " << output << ", retval = " << retval << std::endl;
    }
    return STATUS_SUCCESS;
}

int main() {
    std::string filepath = "/home/user/work/Note2/test/file_test/testfile.txt";
    int retval;
    bool isPassed = true;

    retval = testWriteReadFile(filepath);
    if (retval != STATUS_SUCCESS) {
        std::wcout << "file_test: testWriteReadFile failed" << std::endl;
        isPassed = false;
    }

    std::wcout << "file_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
    return (isPassed) ? STATUS_SUCCESS : STATUS_FAILURE;
}