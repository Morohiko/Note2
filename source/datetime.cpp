#include <iostream>
#include <sstream>

#include "datetime.h"
#include "config.h"
#include "log.h"

// getCurrentDateString: "yyyy/MM/dd"
// getCurrentDateTimeString: "yyyy/MM/dd.hh:mm"

DateTime::DateTime() {
    updateToCurrentDateTime();
}

/**
 * @brief save current date/time from linux date/time to datetime field
 *
 * @return execution status
 */
inline int DateTime::updateToCurrentDateTime() {
    std::time_t result = std::time(nullptr);
    this->datetime = *std::localtime(&result);
    this->datetime.tm_year = this->datetime.tm_year + 1900;
    this->datetime.tm_mon = this->datetime.tm_mon + 1;
    return STATUS_SUCCESS;
}

/**
 * @brief save datetime from tm to datetime field
 *
 * @param[in] tm datetime struct, will be saved to datetime field
 * 
 * @return execution status
 */
int DateTime::updateToCustomDateTime(tm &tm) {
    this->datetime.tm_year = tm.tm_year;
    this->datetime.tm_mon = tm.tm_mon;
    this->datetime.tm_mday = tm.tm_mday;
    this->datetime.tm_hour = tm.tm_hour;
    this->datetime.tm_min = tm.tm_min;
    return STATUS_SUCCESS;
}

/**
 * @brief get saved date from datetime field
 *        format: yyyy/MM/dd
 *
 * @param[out] dest container for getting saved date
 * 
 * @return execution status
 */
int DateTime::getCurrentDateString(std::wstring &dest) {
    dest.clear();
    std::wstring year = std::to_wstring(this->datetime.tm_year);
    while (year.length() < 4) {
        year.insert(0, L"0");
    }
    dest.append(year);
    dest.append(L"/");
    std::wstring month = std::to_wstring(this->datetime.tm_mon);
    while (month.length() < 2) {
        month.insert(0, L"0");
    }
    dest.append(month);
    dest.append(L"/");
    std::wstring day = std::to_wstring(this->datetime.tm_mday);
    while (day.length() < 2) {
        day.insert(0, L"0");
    }
    dest.append(day);
    return STATUS_SUCCESS;
}

/**
 * @brief get saved date/time from datetime field
 *        format: yyyy/MM/dd.hh:mm
 *
 * @param[out] dest container for getting saved date/time
 * 
 * @return execution status
 */
int DateTime::getCurrentDateTimeString(std::wstring &dest) {
    dest.clear();
    std::wstring year = std::to_wstring(this->datetime.tm_year);
    while (year.length() < 4) {
        year.insert(0, L"0");
    }
    dest.append(year);
    dest.append(L"/");
    std::wstring month = std::to_wstring(this->datetime.tm_mon);
    while (month.length() < 2) {
        month.insert(0, L"0");
    }
    dest.append(month);
    dest.append(L"/");
    std::wstring day = std::to_wstring(this->datetime.tm_mday);
    while (day.length() < 2) {
        day.insert(0, L"0");
    }
    dest.append(day);
    dest.append(L".");
    std::wstring hour = std::to_wstring(this->datetime.tm_hour);
    while (hour.length() < 2) {
        hour.insert(0, L"0");
    }
    dest.append(hour);
    dest.append(L":");
    std::wstring min = std::to_wstring(this->datetime.tm_min);
    while (min.length() < 2) {
        min.insert(0, L"0");
    }
    dest.append(min);
    return STATUS_SUCCESS;
}

/**
 * @brief convert tm struct to wstring in datetime convention
 *        format: yyyy/MM/dd
 * 
 * @param[in] tm datetime struct, will be saved to datetime field
 * @param[out] dest container for getting converted date/time
 * 
 * @return execution status
 */
int DateTime::convertTmDateToString(tm &tm, std::wstring &dest) {
    dest.clear();
    if (tm.tm_year < 0 || tm.tm_mon < 0 || tm.tm_mday < 0) {
        WLOG(LOG_ERROR, "tm struct is corrupted");
        return STATUS_FAILURE;
    }

    std::wstring year = std::to_wstring(tm.tm_year);
    WLOG(LOG_WARN, "year = ", year);
    while (year.length() < 4) {
        year.insert(0, L"0");
    }
    dest.append(year);
    dest.append(L"/");
    std::wstring month = std::to_wstring(tm.tm_mon);
    while (month.length() < 2) {
        month.insert(0, L"0");
    }
    dest.append(month);
    dest.append(L"/");
    std::wstring day = std::to_wstring(tm.tm_mday);
    while (day.length() < 2) {
        day.insert(0, L"0");
    }
    dest.append(day);
    return STATUS_SUCCESS;
}
