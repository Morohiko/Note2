#ifndef DUMMY_H
#define DUMMY_H

#include <string>

#include "note.h"

class Dummy {
public:
    void setCallbacks(int (*setFilename)(std::string filename),
                      int (*performReadByDate)(tm *date, std::string *text),
                      int (*performReadAllDate)(std::list<std::string> *dateList),
                      int (*performWriteToFile)(std::string *text, bool isCustomTime, tm *datetime));

public:
// callbacks
    int (*setFilenameHandler)(std::string filename);
    int (*performReadByDateHandler)(tm *date, std::string *text);
    int (*performReadAllDateHandler)(std::list<std::string> *dateList);
    int (*performWriteToFileHandler)(std::string *text, bool isCustomTime, tm *datetime);
};

#endif // DUMMY_H