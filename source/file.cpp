#include <iostream>
#include <fstream>

#include "file.h"
#include "config.h"
#include "log.h"

/**
 * @brief check if file in path is empty
 * 
 * @return true - file is empty, false - if not
 */
bool File::isCurrentFileEmpty() {
    std::wifstream file(this->path.c_str());
    return file.peek() == std::wifstream::traits_type::eof();
}

/**
 * @brief check if file is exist
 *
 * @param[in] filename path to file for check
 * 
 * @return execution status
 */
int File::isFileExists(const std::string &filename) {
    std::wifstream file(filename.c_str());
    return file.good() == true ? STATUS_SUCCESS : STATUS_FILE_NOT_FOUND;
}

/**
 * @brief set path to target file
 *
 * @param[in] src path to file will be saved
 * 
 * @return execution status
 */
int File::setPathToFile(std::string &src) {
    int retval = isFileExists(src);
    if (retval == STATUS_FILE_NOT_FOUND) {
        LOG_ERROR("setPathToFile file with this->path is not exist ");
        return STATUS_FILE_NOT_FOUND;
    }
    this->path = src;
    return STATUS_SUCCESS;
}

/**
 * @brief write to end of file in the path
 *
 * @param[in] src data will be written in the file
 * 
 * @return execution status
 */
int File::writeToEndFile(std::wstring &src) {
    if (this->path.size() < 1) {
        LOG_ERROR("qwriteToEndFile this->path == nullptr");
        return STATUS_FAILURE;
    }
    std::string filename(this->path.length(), '\0');
    for (int i = 0; i < this->path.length(); i++) {
        filename[i] = this->path[i];
    }

    std::ofstream outFile(filename.c_str(), std::ios::out | std::ios::binary | std::ios::app);
    for (int i = 0; i < src.length(); i++) {
        outFile.write((char *) &src.at(i), 2);
    }
    outFile.close();
    return STATUS_SUCCESS;
}

/**
 * @brief read from file
 *
 * @param[in] pos from the position will be read
 * @param[in] size size of data will be read
 * @param[out] output container with read data
 * 
 * @return execution status
 */
int File::readFromFileByPosition(int &pos, int size, std::wstring &output) {
    int retval = isFileExists(this->path);
    if (retval == STATUS_FILE_NOT_FOUND) {
        LOG_ERROR("file with this->path is not exist ");
        return STATUS_FILE_NOT_FOUND;
    }
    std::string filename(this->path.length(), '\0');
    for (int i = 0; i < this->path.length(); i++) {
        filename[i] = this->path[i];
    }
    std::ifstream fin(filename.c_str(), std::ios::binary);

    // check if bom exist
    fin.seekg(pos*2, std::ios::beg);
    std::u16string u16Bom(size, '\0');
    std::streamsize bytes;
    fin.read((char*)&u16Bom[0], 2);
    bytes = fin.gcount();
    if (bytes == 0) {
        fin.close();
        return STATUS_END_OF_FILE;
    }
    wchar_t sym = u16Bom.at(0);
    if ((int)sym == 0xfeff || (int(sym) == 0xfffe)) {
        LOG_DEBUG("skip BOM");
        pos++;
    }
    fin.seekg(pos*2, std::ios::beg);
    std::u16string u16(size, '\0');
    fin.read((char*)&u16[0], size*2);
    bytes = fin.gcount();
    if (bytes == 0) {
        fin.close();
        return STATUS_END_OF_FILE;
    }
    output.resize(size);
    int iout = 0;
    for (int i = 0; i < u16.length(); i++) {
        wchar_t sym = u16.at(i);
        output[iout++] = ((int)u16.at(i));
    }

    fin.close();
    return STATUS_SUCCESS;
}
