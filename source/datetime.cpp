#include <iostream>
#include <sstream>

#include "datetime.h"

// getCurrentDateString: "yyyy/MM/dd"
// getCurrentDateTimeString: "yyyy/MM/dd.hh:mm"

DateTime* DateTime::datetime = nullptr;

DateTime::DateTime() {

}

DateTime* DateTime::getInstance() {
    if (datetime == nullptr) {
        datetime = new DateTime();
    }
    return datetime;
}

inline tm* DateTime::getCurrentTM() {
    std::time_t result = std::time(nullptr);
    return std::localtime(&result);
}

std::string DateTime::getCurrentDateString() {
    tm *datetime = getCurrentTM();
    std::ostringstream oss;
    oss << std::to_string(datetime->tm_year + 1900) << "/" <<
           std::to_string(datetime->tm_mon + 1) << "/" <<
           std::to_string(datetime->tm_mday);
    return oss.str();
}

std::string DateTime::getCurrentDateTimeString() {
    tm *datetime = getCurrentTM();
    std::ostringstream oss;
    oss << std::to_string(datetime->tm_year + 1900) << "/" <<
           std::to_string(datetime->tm_mon + 1) << "/" <<
           std::to_string(datetime->tm_mday) << "." <<
           std::to_string(datetime->tm_hour) << ":" <<
           std::to_string(datetime->tm_min);
    return oss.str();
}
