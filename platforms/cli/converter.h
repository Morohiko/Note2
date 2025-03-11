#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <ctime>

#include "log.h"

class Converter {
public:
    static inline void date_string_to_tm(std::wstring &date, tm &tm) {
        LOG_INFO(date);
    
        tm.tm_year = std::stoi(date.substr(0, 4));
        tm.tm_mon = std::stoi(date.substr(5, 2));
        tm.tm_mday = std::stoi(date.substr(8, 2));
    }

    static inline std::string wstring_to_utf8(const std::wstring& wstr) {
        // Create a converter object using UTF-8 encoding.
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }
};

#endif // CONVERTER_H
