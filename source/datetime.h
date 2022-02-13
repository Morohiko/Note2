#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <string>

// singleton class-helper for
// read/convert datetime
class DateTime {
    static DateTime *datetime;
    inline tm* getCurrentTM();

    DateTime();

public:
    static DateTime* getInstance();
    std::string getCurrentDateString();
    std::string getCurrentDateTimeString();
};

#endif // DATETIME_H
