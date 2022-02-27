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
    static int setFilenameHandler(std::string filename);
    static int performReadByDateHandler(tm *date, std::string *text, std::string *key);
    static int performReadAllDateHandler(std::list<std::string> *dateList, std::string *key);
    static int performWriteToFileHandler(std::string *text, bool isCustomTime, tm *datetime, std::string *key);
#endif

private:
    // MainWindow window;
    File file;
    Encoder encoder;
    Parser parser;
    DateTime datetime;

    int setFilename(std::string filename);
    int performReadByDate(tm *date, std::string *text, std::string &key);
    int performReadAllDate(std::list<std::string> *dateList, std::string &key);
    int performWriteToFile(std::string &text, bool isCustomTime, tm* currentDateTime, std::string &key);

#ifdef WITH_ENCODER
    std::string performEncodeString(std::string *text, std::string &key);
    std::string performDecodeString(std::string *text, std::string &key);
#endif

    int findPositionByHeader(int pos, std::string &header, std::string &key);
    int findPositionByDate(int pos, std::string date, int &returnedPosition, std::string &key);
    int performReadBodyByHead(std::string head, std::string &body, std::string &key);

    bool isValidKey(std::string &key);
};

#endif // NOTE_H
