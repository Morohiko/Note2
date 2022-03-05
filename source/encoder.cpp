#include <string>
#include <cassert>
#include <iostream>

#include "encoder.h"

std::wstring Encoder::encodeStringByKey(std::wstring &src, std::wstring &key) {
    std::wstring dest;
    int nkey = 0;

    for (int i = 0; i < src.size(); i++) {
        uint32_t buff = src.at(i) + key.at(nkey);
        dest.push_back(buff);
        if (key.size() <= ++nkey) nkey = 0;
    }
    return dest;
}


std::wstring Encoder::decodeStringByKey(std::wstring &src, std::wstring &key) {
    std::wstring dest;
    int nkey = 0;
    for (int i = 0; i < src.size(); i++) {
        uint32_t buff = src.at(i) > key.at(nkey) ? src.at(i) - key.at(nkey) : key.at(nkey) - src.at(i);
        dest.push_back(buff);
        if (key.size() <= ++nkey) nkey = 0;
    }
    return dest;
}
