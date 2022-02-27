#include <string>
#include <cassert>
#include <iostream>

#include "encoder.h"

std::string Encoder::encodeStringByKey(std::string &src, std::string &key) {
    std::string dest;
    int nkey = 0;

    for (int i = 0; i < src.size(); i++) {
        char buff = src.at(i) + key.at(nkey);
        dest.push_back(buff);
        if (key.size() <= ++nkey) nkey = 0;
    }
    return dest;
}


std::string Encoder::decodeStringByKey(std::string &src, std::string &key) {
    std::string dest;

    int nkey = 0;
    for (int i = 0; i < src.size(); i++) {
        char buff = src.at(i) - key.at(nkey);
        dest.push_back(buff);
        if (key.size() <= ++nkey) nkey = 0;
    }
    return dest;
}
