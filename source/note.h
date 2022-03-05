#ifndef NOTE_H
#define NOTE_H

#include <list>
#ifdef USE_QT
#include <QDateTime>
#endif
#include "file.h"
#include "encoder.h"
#include "parser.h"
#include "config.h"
#include "datetime.h"

class Note;
static Note *note = nullptr;

class Note
{
public:
    Note();
    // int start();
#ifdef USE_QT
    static int setFilenameHandler(QString *filename);
    static int performReadByDateHandler(QDate *date, QString *text, QString *key);
    static int performReadAllDateHandler(QList<QDate *> *dateList, QString *key);
    static int performWriteToFileHandler(QString *text, bool isCustomTime, QDateTime *datetime, QString *key);
#endif

#ifdef USE_ANDROID
    // TODO: android api
#endif

#ifdef USE_DUMMY
    static int setFilenameHandler(std::string *filename);
    static int performReadByDateHandler(tm *date, std::wstring *text, std::wstring *key);
    static int performReadAllDateHandler(std::list<std::wstring> *dateList, std::wstring *key);
    static int performWriteToFileHandler(std::wstring *text, bool isCustomTime, tm *datetime, std::wstring *key);
#endif

private:
    File file;
    Encoder encoder;
    Parser parser;
    DateTime datetime;

    int setFilename(std::string &filename);
    int performReadByDate(tm &date, std::wstring &text, std::wstring &key);
    int performReadAllDate(std::list<std::wstring> &dateList, std::wstring &key);
    int performWriteToFile(std::wstring &text, bool isCustomTime, tm& currentDateTime, std::wstring &key);

#ifdef WITH_ENCODER
    std::wstring performEncodeString(std::wstring &text, std::wstring &key);
    std::wstring performDecodeString(std::wstring &text, std::wstring &key);
#endif

    int findPositionByHeader(int pos, std::wstring &header, std::wstring &key);
    int findPositionByDate(int &pos, std::wstring &date, std::wstring &key);
    int performReadBodyByHead(std::wstring &head, std::wstring &body, std::wstring &key);

    bool isValidKey(std::wstring &key);
};

#endif // NOTE_H
