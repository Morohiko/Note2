#include "dummy.h"
#include <iostream>

void Dummy::setCallbacks(int (*setFilename)(std::string filename),
                         int (*performReadByDate)(tm *date, std::string *text, std::string *key),
                         int (*performReadAllDate)(std::list<std::string> *dateList, std::string *key),
                         int (*performWriteToFile)(std::string *text, bool isCustomTime, tm *datetime, std::string *key)) {
    setFilenameHandler = setFilename;
    performReadByDateHandler = performReadByDate;
    performReadAllDateHandler = performReadAllDate;
    performWriteToFileHandler = performWriteToFile;
}
