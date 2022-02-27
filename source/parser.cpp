#include <cassert>
#include <iostream>
#include <stdexcept>

#include "parser.h"
#include "config.h"

Parser::Parser() {}

// 2022/2/19.23:32_000030
int Parser::parseHeadFromString(std::string &text, std::string &date, int &size) {
    int retval = 0;
    if (text.length() < SIZE_OF_HEADER) {
        std::cout << "ERROR: cant parse head, string is corrupted: head = " << text << std::endl;
        return STATUS_FAILURE;
    }
    retval = parseHeadFromStringGetDateString(text, date);
    if (retval != STATUS_SUCCESS) {
        std::cout << "ERROR: cant parse head on get date step: head = " << text << std::endl;
        return retval;
    }
    retval = parseHeadFromStringGetSize(text, size);
    if (retval != STATUS_SUCCESS) {
        std::cout << "ERROR: cant parse head on get size step: head = " << text << std::endl;
        return retval;
    }
    return retval;
}

int Parser::parseHeadFromStringGetDateString(std::string &text, std::string &date) {
    // 10 - size of date in header
    if (text.length() < SIZE_OF_DATE ) {
        std::cout << "ERROR: cant parse time from header: text = " << text <<
        ", text.length = " << text.length() << std::endl;
        return STATUS_FAILURE;
    }
    std::cout << LOG_DEBUG << "text  = " << text << std::endl;
    date = text.substr(0, SIZE_OF_DATE);
    return STATUS_SUCCESS;
}

int Parser::parseHeadFromStringGetTimeString(std::string &text, std::string &time) {
    // 15 - size of date and time in header
    if (text.length() < 15) {
        std::cout << "ERROR: cant parse time from header: text = " << text <<
        ", text.length = " << text.length() << std::endl;
        return STATUS_FAILURE;
    }
    time = text.substr(SIZE_OF_DATE + 1, SIZE_OF_TIME);
    return STATUS_SUCCESS;
}

int Parser::parseHeadFromStringGetSize(std::string &text, int &size) {
    int iter = 0;
    if (text.length() < SIZE_OF_HEADER) {
        std::cout << "ERROR: header was broken: " <<
                    "text.size = " << text.size() << std::endl;
        return STATUS_FAILURE;
    }
    std::string sizeString = text.substr(17, 6);
    if (sizeString.length() != SIZE_OF_SIZE) {
        std::cout << "ERROR: cant parse size from header: " <<
            "sizeString.length() = " << sizeString.length() << 
            ", sizeString = " << sizeString << std::endl;
        return STATUS_FAILURE;
    }
    for (size_t i = 0; i < sizeString.length(); i++) {
        try {
            int tmp = std::stoi(sizeString.substr(i, i+1));
        } catch(std::invalid_argument& e){
            std::cout << "ERROR: cant parse size from header, corrupted data in header: " <<
                "sizeString = " << sizeString << std::endl;
            return STATUS_FAILURE;
        }
    }
    try {
        size = std::stoi(sizeString);
    } catch(std::invalid_argument& e){
        std::cout << "ERROR: cant parse size from header, corrupted data in header: " <<
                "sizeString = " << sizeString << std::endl;
        return STATUS_FAILURE;
    }
    return 0;
}

std::string Parser::generateStringFromSize(int size) {
    std::string sizeBuff = std::to_string(size);
    while (sizeBuff.size() < 6) {
        sizeBuff = "0" + sizeBuff;
    }
    return sizeBuff;
}

std::string Parser::generateHead(std::string &currentDateTime, int size) {
    std::string text;
    text.append(currentDateTime);
    text.append("_");
    text.append(generateStringFromSize(size));
    text.append("_");
    return text;
}
