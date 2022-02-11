#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QDate>

class Parser
{
public:
    Parser();

    int parseHeadFromQString(QString *text, QDate *date, int *size);
    int parseHeadFromQStringGetSize(QString *text, int *size);
    int parseHeadFromQStringGetDateString(QString *text, QString *date);
    int parseHeadFromQStringGetTimeString(QString *text, QString *time);

    QString parseStringFromQDateTime(QDateTime *datetime);
    QString parseStringFromQDate(QDate *date);
    QString parseStringFromSize(int size);

    QString generateHead(QDateTime *datetime, int size);
};

#endif // PARSER_H
