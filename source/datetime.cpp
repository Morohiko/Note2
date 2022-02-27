#include <iostream>
#include <sstream>

#include "datetime.h"

// getCurrentDateString: "yyyy/MM/dd"
// getCurrentDateTimeString: "yyyy/MM/dd.hh:mm"

DateTime::DateTime() {
    updateToCurrentDateTime();
}

inline void DateTime::updateToCurrentDateTime() {
    std::time_t result = std::time(nullptr);
    this->datetime = *std::localtime(&result);
    this->datetime.tm_year = this->datetime.tm_year + 1900;
    this->datetime.tm_mon = this->datetime.tm_mon + 1;
}

void DateTime::updateToCustomDateTime(tm *tm) {
    this->datetime.tm_year = tm->tm_year;
    this->datetime.tm_mon = tm->tm_mon;
    this->datetime.tm_mday = tm->tm_mday;
    this->datetime.tm_hour = tm->tm_hour;
    this->datetime.tm_min = tm->tm_min;
}

// time format 2022/02/22
std::string DateTime::getCurrentDateString() {
    std::string year = std::to_string(this->datetime.tm_year);
    while (year.length() < 4) {
        year.insert(0, "0");
    }
    std::string month = std::to_string(this->datetime.tm_mon);
    while (month.length() < 2) {
        month.insert(0, "0");
    }
    std::string day = std::to_string(this->datetime.tm_mday);
    while (day.length() < 2) {
        day.insert(0, "0");
    }

    std::ostringstream oss;
    oss << year << "/" << month << "/" << day;
    return oss.str();
}

// datetime format 2022/02/22.20:02
std::string DateTime::getCurrentDateTimeString() {
    std::string year = std::to_string(this->datetime.tm_year);
    while (year.length() < 4) {
        year.insert(0, "0");
    }
    std::string month = std::to_string(this->datetime.tm_mon);
    while (month.length() < 2) {
        month.insert(0, "0");
    }
    std::string day = std::to_string(this->datetime.tm_mday);
    while (day.length() < 2) {
        day.insert(0, "0");
    }
    std::string hour = std::to_string(this->datetime.tm_hour);
    while (hour.length() < 2) {
        hour.insert(0, "0");
    }
    std::string min = std::to_string(this->datetime.tm_min);
    while (min.length() < 2) {
        min.insert(0, "0");
    }
    std::ostringstream oss;
    oss << year << "/" << month << "/" << day << "." <<
           hour << ":" << min;
    return oss.str();
}

// time format 2022/02/22
std::string DateTime::convertTmDateToString(tm *tm) {
    std::string year = std::to_string(tm->tm_year);
    while (year.length() < 4) {
        year.insert(0, "0");
    }
    std::string month = std::to_string(tm->tm_mon);
    while (month.length() < 2) {
        month.insert(0, "0");
    }
    std::string day = std::to_string(tm->tm_mday);
    while (day.length() < 2) {
        day.insert(0, "0");
    }
    std::ostringstream oss;
    oss << year << "/" << month << "/" << day;
    return oss.str();
}
