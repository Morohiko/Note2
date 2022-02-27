#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <string>

// singleton class-helper for
// read/convert datetime
class DateTime {
    tm datetime;

public:
    DateTime();

    void updateToCurrentDateTime();
    void updateToCustomDateTime(tm *tm);

    std::string getCurrentDateString();
    std::string getCurrentDateTimeString();
    std::string convertTmDateToString(tm *tm);
};

#endif // DATETIME_H
