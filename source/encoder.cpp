#include <string>
#include <cassert>
#include <iostream>

#include "encoder.h"

/**
 * @brief encode src by key and save to dest
 *
 * @param[in] src data will be ecodded
 * @param[in] key using for encoding
 * @param[out] dest container for saving encodded data
 * 
 * @return execution status
 */
int Encoder::encodeStringByKey(std::wstring &src, std::wstring &key, std::wstring &dest) {
    int nkey = 0;
    for (int i = 0; i < src.size(); i++) {
        uint32_t buff;
        if (key.size() != 0) {
            buff = src.at(i) + key.at(nkey);
        } else {
            buff = src.at(i);
        }
        dest.push_back(buff);
        if (key.size() != 0 && key.size() <= ++nkey) nkey = 0;
    }
    return STATUS_SUCCESS;
}

/**
 * @brief decode src by key and save to dest
 *
 * @param[in] src data will be decoded
 * @param[in] key using for decoding
 * @param[out] dest container for saving decodded data
 * 
 * @return execution status
 */
int Encoder::decodeStringByKey(std::wstring &src, std::wstring &key, std::wstring &dest) {
    int nkey = 0;
    for (int i = 0; i < src.size(); i++) {
        uint32_t buff;
        if (key.size() != 0) {
            buff = src.at(i) > key.at(nkey) ? src.at(i) - key.at(nkey) : key.at(nkey) - src.at(i);
        } else {
            buff = src.at(i);
        }
        dest.push_back(buff);
        if (key.size() != 0 && key.size() <= ++nkey) nkey = 0;
    }
    return STATUS_SUCCESS;
}
