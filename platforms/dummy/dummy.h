#ifndef DUMMY_H
#define DUMMY_H

#include <string>

#include "note.h"

class Dummy {
public:
    void setCallbacks(int (*setFilename)(std::string *filename),
                      int (*performReadByDate)(tm *date, std::wstring *text, std::wstring *key),
                      int (*performReadAllDate)(std::list<std::wstring> *dateList, std::wstring *key),
                      int (*performWriteToFile)(std::wstring *text, bool isCustomTime, tm *datetime, std::wstring *key));

public:
// callbacks
    int (*setFilenameHandler)(std::string *filename);
    int (*performReadByDateHandler)(tm *date, std::wstring *text, std::wstring *key);
    int (*performReadAllDateHandler)(std::list<std::wstring> *dateList, std::wstring *key);
    int (*performWriteToFileHandler)(std::wstring *text, bool isCustomTime, tm *datetime, std::wstring *key);
};

#endif // DUMMY_H