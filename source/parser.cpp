#include <cassert>
#include <iostream>
#include <stdexcept>

#include "parser.h"
#include "config.h"

Parser::Parser() {}

int Parser::parseHeadFromString(std::wstring &text, std::wstring &date, int &size) {
    int retval = 0;
    std::wcout << LOG_ERROR << "text.length() = " << text.length() << ", text = " << text << std::endl;
    if (text.length()*2 < SIZE_OF_HEADER) {
        std::wcout << "ERROR: cant parse head, string is corrupted: head = " << text << std::endl;
        return STATUS_FAILURE;
    }
    retval = parseHeadFromStringGetDateString(text, date);
    if (retval != STATUS_SUCCESS) {
        std::wcout << "ERROR: cant parse head on get date step: head = " << text << std::endl;
        return retval;
    }
    retval = parseHeadFromStringGetSize(text, size);
    if (retval != STATUS_SUCCESS) {
        std::wcout << "ERROR: cant parse head on get size step: head = " << text << std::endl;
        return retval;
    }
    return retval;
}

int Parser::parseHeadFromStringGetDateString(std::wstring &text, std::wstring &date) {
    // 10 - size of date in header
    if (text.length() < SIZE_OF_DATE ) {
        std::wcout << "ERROR: cant parse time from header: text = " << text <<
                      ", text.length = " << text.length() << std::endl;
        return STATUS_FAILURE;
    }
    std::wcout << LOG_DEBUG << "text  = " << text << std::endl;
    date = text.substr(DATE_POSITION, SIZE_OF_DATE);
    return STATUS_SUCCESS;
}

int Parser::parseHeadFromStringGetTimeString(std::wstring &text, std::wstring &time) {
    // 15 - size of date and time in header
    if (text.length() < SIZE_OF_TIME) {
        std::wcout << "ERROR: cant parse time from header: text = " << text <<
        ", text.length = " << text.length() << std::endl;
        return STATUS_FAILURE;
    }
    time = text.substr(TIME_POSITION, SIZE_OF_TIME);
    return STATUS_SUCCESS;
}

int Parser::parseHeadFromStringGetSize(std::wstring &text, int &size) {
    int iter = 0;
    if (text.length()*2 < SIZE_OF_HEADER) {
        std::wcout << "ERROR: header was broken: " <<
                    "text.size = " << text.size() << std::endl;
        return STATUS_FAILURE;
    }
    std::wstring sizeString = text.substr(SIZE_POSITION, SIZE_OF_SIZE);
    if (sizeString.length() != SIZE_OF_SIZE) {
        std::wcout << "ERROR: cant parse size from header: " <<
            "sizeString.length() = " << sizeString.length() << 
            ", sizeString = " << sizeString << std::endl;
        return STATUS_FAILURE;
    }
    for (size_t i = 0; i < sizeString.length(); i++) {
        try {
            int tmp = std::stoi(sizeString.substr(i, i+1));
        } catch(std::invalid_argument& e){
            std::wcout << "ERROR: cant parse size from header, corrupted data in header: " <<
                "sizeString = " << sizeString << std::endl;
            return STATUS_FAILURE;
        }
    }
    try {
        size = std::stoi(sizeString);
    } catch(std::invalid_argument& e){
        std::wcout << "ERROR: cant parse size from header, corrupted data in header: " <<
                "sizeString = " << sizeString << std::endl;
        return STATUS_FAILURE;
    }
    return 0;
}

std::wstring Parser::generateStringFromSize(int size) {
    std::wstring sizeBuff = std::to_wstring(size);
    while (sizeBuff.size() < SIZE_OF_SIZE) {
        sizeBuff = L"0" + sizeBuff;
    }
    return sizeBuff;
}

std::wstring Parser::generateHead(std::wstring &currentDateTime, int size) {
    std::wstring text;
    text.append(currentDateTime);
    text.append(L"_");
    text.append(generateStringFromSize(size));
    text.append(L"_");
    return text;
}
