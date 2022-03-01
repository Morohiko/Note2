#include <iostream>
#include <fstream>

#include "file.h"
#include "config.h"

bool File::isCurrentFileEmpty() {
    std::wifstream file(this->path.c_str());
    return file.peek() == std::wifstream::traits_type::eof();
}

int File::isFileExists(const std::string &filename) {
    std::wifstream file(filename.c_str());
    return file.good() == true ? STATUS_SUCCESS : STATUS_FILE_NOT_FOUND;
}

int File::setPathToFile(std::string &src) {
    int retval = isFileExists(src);
    if (retval == STATUS_FILE_NOT_FOUND) {
        std::cout << LOG_ERROR << "setPathToFile file with this->path is not exist " << src << std::endl;
        return STATUS_FILE_NOT_FOUND;
    }
    this->path = src;
    return STATUS_SUCCESS;
}

int File::writeToEndFile(std::wstring &src) {
    if (this->path.size() < 1) {
        std::wcout  << LOG_ERROR << "qwriteToEndFile this->path == nullptr";
        return -1;
    }
    std::wofstream out;
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    out.open(this->path, std::ios::app);
    out << src;
    return 0;
}
#include <codecvt>
#include <sstream>

int File::readFromFileByPosition(int pos, int size, std::wstring &output) {
    int retval = isFileExists(this->path);
    if (retval == STATUS_FILE_NOT_FOUND) {
        std::cout << LOG_ERROR << "file with this->path is not exist " << this->path << std::endl;
        return STATUS_FILE_NOT_FOUND;
    }
    std::wifstream file(this->path, std::ios::ate|std::ios::binary);
    int filesize;
    if (file.is_open()) {
        filesize = file.tellg();
        if (pos >= filesize) {
            return STATUS_END_OF_FILE;
        }
        file.seekg(pos, std::ios::beg);
        output.resize(size);
        file.read(&output[0], size);
    } else {
        std::wcout << LOG_DEBUG << "file is closed" << std::endl;
    }
    return STATUS_SUCCESS;
}
