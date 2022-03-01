#include "dummy.h"
#include <iostream>

void Dummy::setCallbacks(int (*setFilename)(std::string *filename),
                         int (*performReadByDate)(tm *date, std::wstring *text, std::wstring *key),
                         int (*performReadAllDate)(std::list<std::wstring> *dateList, std::wstring *key),
                         int (*performWriteToFile)(std::wstring *text, bool isCustomTime, tm *datetime, std::wstring *key)) {
    setFilenameHandler = setFilename;
    performReadByDateHandler = performReadByDate;
    performReadAllDateHandler = performReadAllDate;
    performWriteToFileHandler = performWriteToFile;
}
