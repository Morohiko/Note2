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
    std::string filename(this->path.length(), '\0');
    for (int i = 0; i < this->path.length(); i++) {
        filename[i] = this->path[i];
    }

    std::ofstream outFile(filename.c_str(), std::ios::out | std::ios::binary);
    for (int i = 0; i < src.length(); i++) {
        outFile.write((char *) &src.at(i), 2);
    }
    outFile.close();
    return 0;
}

int File::readFromFileByPosition(int &pos, int size, std::wstring &output) {
    int retval = isFileExists(this->path);
    if (retval == STATUS_FILE_NOT_FOUND) {
        std::cout << LOG_ERROR << "file with this->path is not exist " << this->path << std::endl;
        return STATUS_FILE_NOT_FOUND;
    }
    std::string filename(this->path.length(), '\0');
    for (int i = 0; i < this->path.length(); i++) {
        filename[i] = this->path[i];
    }
    std::ifstream fin(filename.c_str(), std::ios::binary);

    // check if bom exist
    fin.seekg(pos*2, std::ios::beg);
    std::u16string u16Bom(size, '\0'); // +2 in case bom
    fin.read((char*)&u16Bom[0], 2);
    wchar_t sym = u16Bom.at(0);
    if ((int)sym == 0xfeff || (int(sym) == 0xfffe)) {
        std::wcout << LOG_DEBUG << "skip BOM" << std::endl;
        pos++;
    }
    fin.seekg(pos*2, std::ios::beg);
    std::u16string u16(size, '\0'); // +2 in case bom
    fin.read((char*)&u16[0], size*2);
    output.resize(size);
    int iout = 0;
    for (int i = 0; i < u16.length(); i++) {
        wchar_t sym = u16.at(i);
        output[iout++] = ((int)u16.at(i));
    }
    fin.close();
    return STATUS_SUCCESS;
}
