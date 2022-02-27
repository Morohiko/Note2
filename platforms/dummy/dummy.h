#ifndef DUMMY_H
#define DUMMY_H

#include <string>

#include "note.h"

class Dummy {
public:
    void setCallbacks(int (*setFilename)(std::string filename),
                      int (*performReadByDate)(tm *date, std::string *text, std::string *key),
                      int (*performReadAllDate)(std::list<std::string> *dateList, std::string *key),
                      int (*performWriteToFile)(std::string *text, bool isCustomTime, tm *datetime, std::string *key));

public:
// callbacks
    int (*setFilenameHandler)(std::string filename);
    int (*performReadByDateHandler)(tm *date, std::string *text, std::string *key);
    int (*performReadAllDateHandler)(std::list<std::string> *dateList, std::string *key);
    int (*performWriteToFileHandler)(std::string *text, bool isCustomTime, tm *datetime, std::string *key);
};

#endif // DUMMY_H