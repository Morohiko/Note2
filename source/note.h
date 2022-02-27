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
    static int performReadByDateHandler(QDate *date, QString *text);
    static int performReadAllDateHandler(QList<QDate *> *dateList);
    static int performWriteToFileHandler(QString *text, bool isCustomTime, QDateTime *datetime);
#endif

#ifdef USE_ANDROID
    // TODO: android api
#endif

#ifdef USE_DUMMY
    static int setFilenameHandler(std::string filename);
    static int performReadByDateHandler(tm *date, std::string *text);
    static int performReadAllDateHandler(std::list<std::string> *dateList);
    static int performWriteToFileHandler(std::string *text, bool isCustomTime, tm *datetime);
#endif

private:
    // MainWindow window;
    File file;
    Encoder encoder;
    Parser parser;
    DateTime datetime;

    int setFilename(std::string filename);
    int performReadByDate(tm *date, std::string *text);
    int performReadAllDate(std::list<std::string> *dateList);
    int performWriteToFile(std::string text, bool isCustomTime, tm* currentDateTime);

#ifdef WITH_ENCODER
    std::string performEncodeString(std::string *text);
    std::string performDecodeString(std::string *text);
#endif

    int findPositionByHeader(int pos, std::string header);
    int findPositionByDate(int pos, std::string date, int &returnedPosition);
    int performReadBodyByHead(std::string head, std::string &body);

    bool isValidKey();
};

#endif // NOTE_H
