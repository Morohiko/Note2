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
    void updateToCustomDateTime(tm &tm);

    std::wstring getCurrentDateString();
    std::wstring getCurrentDateTimeString();
    std::wstring convertTmDateToString(tm &tm);
};

#endif // DATETIME_H
