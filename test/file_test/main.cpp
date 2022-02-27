#include <iostream>
#include <fstream>
#include <string>

#include "file.h"
#include "config.h"

#define PATH_FILE "/home/user/work/Note2/test/file_test/testfile.txt"

// **************** help functions ******************* //
bool isFileExists(std::string &name) {
    std::ifstream f(name.c_str());
    return f.good();
}

int createFile(std::string &name) {
    std::ofstream MyFile(name);
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
    std::string test_text = "test_text";
    file.writeToEndFile(test_text);
    file.writeToEndFile(test_text);
    for (int i = 0; i < 40; i+=5) {
        std::string output;
        int retval = file.readFromFileByPosition(i, 5, output);
        std::cout << "output = " << output << ", retval = " << retval << std::endl;
    }
    return STATUS_SUCCESS;
}

int main() {
    std::string filepath = "/home/user/work/Note2/test/file_test/testfile.txt";
    int retval;
    bool isPassed = true;

    retval = testWriteReadFile(filepath);
    if (retval != STATUS_SUCCESS) {
        std::cout << "file_test: testWriteReadFile failed" << std::endl;
        isPassed = false;
    }

    std::cout << "file_test: done " << ((isPassed) ? "passed" : "failed") << std::endl;
}