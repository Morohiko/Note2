#include <cassert>
#include <iostream>
#include <stdexcept>

#include "parser.h"
#include "config.h"

Parser::Parser() {}

/**
 * @brief parse date and size from text
 *
 * @param[in] text input text with head
 * @param[out] date parsed date
 * @param[out] size parsed size
 * 
 * @return execution status
 */
int Parser::parseHeadFromString(std::wstring &text, std::wstring &date, int &size) {
    int retval = 0;
    std::wcout << LOG_DEBUG << "text.length() = " << text.length() << ", text = " << text << std::endl;
    if (text.length()*2 < SIZE_OF_HEADER) {
        std::wcout << LOG_ERROR << "cant parse head, string is corrupted: head = " << text << std::endl;
        return STATUS_FAILURE;
    }
    retval = parseHeadFromStringGetDateString(text, date);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant parse head on get date step: head = " << text << std::endl;
        return retval;
    }
    retval = parseHeadFromStringGetSize(text, size);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant parse head on get size step: head = " << text << std::endl;
        return retval;
    }
    return retval;
}

/**
 * @brief parse date from text
 *
 * @param[in] text input text with head
 * @param[out] date parsed date
 * 
 * @return execution status
 */
int Parser::parseHeadFromStringGetDateString(std::wstring &text, std::wstring &date) {
    if (text.length() < SIZE_OF_DATE ) {
        std::wcout << LOG_ERROR << "cant parse time from header: text = " << text <<
                      ", text.length = " << text.length() << std::endl;
        return STATUS_FAILURE;
    }
    std::wcout << LOG_DEBUG << "text  = " << text << std::endl;
    date = text.substr(DATE_POSITION, SIZE_OF_DATE);
    return STATUS_SUCCESS;
}

/**
 * @brief parse time from text
 *
 * @param[in] text input text with head
 * @param[out] time parsed time
 * 
 * @return execution status
 */
int Parser::parseHeadFromStringGetTimeString(std::wstring &text, std::wstring &time) {
    if (text.length() < SIZE_OF_TIME) {
        std::wcout << LOG_ERROR << "cant parse time from header: text = " << text <<
        ", text.length = " << text.length() << std::endl;
        return STATUS_FAILURE;
    }
    time = text.substr(TIME_POSITION, SIZE_OF_TIME);
    return STATUS_SUCCESS;
}

/**
 * @brief parse size from text
 *
 * @param[in] text input text with head
 * @param[out] size parsed size
 * 
 * @return execution status
 */
int Parser::parseHeadFromStringGetSize(std::wstring &text, int &size) {
    if (text.length()*2 < SIZE_OF_HEADER) {
        std::wcout << LOG_ERROR << "header was broken: " <<
                    "text.size = " << text.size() << std::endl;
        return STATUS_FAILURE;
    }
    std::wstring sizeString = text.substr(SIZE_POSITION, SIZE_OF_SIZE);
    if (sizeString.length() != SIZE_OF_SIZE) {
        std::wcout << LOG_ERROR << "cant parse size from header: " <<
            "sizeString.length() = " << sizeString.length() << 
            ", sizeString = " << sizeString << std::endl;
        return STATUS_FAILURE;
    }
    for (size_t i = 0; i < sizeString.length(); i++) {
        try {
            int tmp = std::stoi(sizeString.substr(i, i+1));
        } catch(std::invalid_argument& e){
            std::wcout << LOG_ERROR << "cant parse size from header, corrupted data in header: " <<
                "sizeString = " << sizeString << std::endl;
            return STATUS_FAILURE;
        }
    }
    try {
        size = std::stoi(sizeString);
    } catch(std::invalid_argument& e){
        std::wcout << LOG_ERROR << "cant parse size from header, corrupted data in header: " <<
                "sizeString = " << sizeString << std::endl;
        return STATUS_FAILURE;
    }
    return STATUS_SUCCESS;
}

/**
 * @brief generate size string from int size
 *
 * @param[in] size size in int
 * @param[out] dest generated string size
 * 
 * @return execution status
 */
int Parser::generateStringFromSize(int size, std::wstring &dest) {
    dest = std::to_wstring(size);
    while (dest.size() < SIZE_OF_SIZE) {
        dest = L"0" + dest;
    }
    return STATUS_SUCCESS;
}

/**
 * @brief generate head from date and size
 *
 * @param[in] currentDateTime date for head
 * @param[in] size size for head
 * @param[out] dest generated head with date and size
 * 
 * @return execution status
 */
int Parser::generateHead(std::wstring &currentDateTime, int size, std::wstring &dest) {
    std::wstring sizeString;
    int retval;
    retval = generateStringFromSize(size, sizeString);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant generate string from size" << std::endl;
        return STATUS_FAILURE;
    }
    dest.append(currentDateTime);
    dest.append(L"_");
    dest.append(sizeString);
    dest.append(L"_");
    return STATUS_SUCCESS;
}
