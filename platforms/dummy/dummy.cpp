#include "dummy.h"
#include <iostream>

void Dummy::setCallbacks(int (*setFilename)(std::string filename),
                         int (*performReadByDate)(tm *date, std::string *text),
                         int (*performReadAllDate)(std::list<std::string> *dateList),
                         int (*performWriteToFile)(std::string *text, bool isCustomTime, tm *datetime)) {
    setFilenameHandler = setFilename;
    performReadByDateHandler = performReadByDate;
    performReadAllDateHandler = performReadAllDate;
    performWriteToFileHandler = performWriteToFile;
}
