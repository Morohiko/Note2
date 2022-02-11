#ifndef NOTE_H
#define NOTE_H

#include "mainwindow.h"
#include "file.h"
#include "encoder.h"
#include "parser.h"
#include "config.h"

class Note;
static Note *note = nullptr;

class Note
{
public:
    Note();
    int start();
private:
    MainWindow window;
    File file;
    Encoder encoder;
    Parser parser;

    static void setFilenameHandler(QString filename);
    static int performReadByDateHandler(QDate *date, QString *text);
    static int performReadAllDateHandler(QList<QDate *> *dateList);
    static int performWriteToFileHandler(QString text);

    void setFilename(QString filename);
    int performReadByDate(QDate *date, QString *text);
    int performReadAllDate(QList<QDate *> *dateList);
    int performWriteToFile(QString text);

#ifdef WITH_ENCODER
    QString performEncodeString(QString *text);
    QString performDecodeString(QString *text);
#endif

    int findPositionByHeader(int pos, QString header);
    int findPositionByDate(int pos, QString date);
    QString performReadBodyByHead(QString head);

    bool isValidKey();
};

#endif // NOTE_H
