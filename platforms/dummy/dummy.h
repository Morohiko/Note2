#ifndef DUMMY_H
#define DUMMY_H

#include <string>

#include "note.h"

class Dummy {
public:
    void setCallbacks(int (*setFilename)(std::string &filename),
                      int (*performReadByDate)(tm &date, std::wstring &key, std::wstring &outputBody),
                      int (*performReadAllDate)(std::wstring &key, std::list<std::wstring> &dateList),
                      int (*performWriteToFile)(std::wstring &text, bool isCustomTime, tm &datetime, std::wstring &key));

public:
// callbacks
    int (*setFilenameHandler)(std::string &filename);
    int (*performReadByDateHandler)(tm &date, std::wstring &key, std::wstring &outputBody);
    int (*performReadAllDateHandler)(std::wstring &key, std::list<std::wstring> &dateList);
    int (*performWriteToFileHandler)(std::wstring &text, bool isCustomTime, tm &datetime, std::wstring &key);
};

#endif // DUMMY_H