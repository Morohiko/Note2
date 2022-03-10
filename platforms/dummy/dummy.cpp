#include <iostream>

#include "dummy.h"

void Dummy::setCallbacks(int (*setFilename)(std::string &filename),
                         int (*performReadByDate)(tm &date, std::wstring &key, std::wstring &outputBody),
                         int (*performReadAllDate)(std::wstring &key, std::list<std::wstring> &dateList),
                         int (*performWriteToFile)(std::wstring &text, bool isCustomTime, tm &datetime, std::wstring &key)) {
    setFilenameHandler = setFilename;
    performReadByDateHandler = performReadByDate;
    performReadAllDateHandler = performReadAllDate;
    performWriteToFileHandler = performWriteToFile;
}
