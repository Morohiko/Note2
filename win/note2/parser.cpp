#include "parser.h"

#include <QDebug>

#define DATEFORMAT "yyyy/MM/dd"
#define DATETIMEFORMAT "yyyy/MM/dd.hh:mm"

Parser::Parser() {}

// _date_time_size_, example format: _20190203095420_ <- _2019.02.03_09:54_20_
int Parser::parseHeadFromQString(QString *text, QDate *date, int *size) {
    Q_ASSERT(text); Q_ASSERT(date); Q_ASSERT(size);

    QString dateString = text->left(10);

    qDebug() << "DEBUG: leftString = " << dateString;

    *date = QDate::fromString(dateString, DATEFORMAT);

    int retval = 0;
    retval = parseHeadFromQStringGetSize(text, size);
    qDebug() << "DEBUG: parseHead: year = " << date->year() << ", month = " << date->month() << ", day = " << date->day() << ", size = " << *size;

    return retval;
}

int Parser::parseHeadFromQStringGetDateString(QString *text, QString *date) {
    Q_ASSERT(text); Q_ASSERT(date);
    *date = text->left(10);
    return 0;
}

int Parser::parseHeadFromQStringGetTimeString(QString *text, QString *time) {
    Q_ASSERT(text); Q_ASSERT(time);
    *time = text->left(16).right(5);
    return 0;
}

int Parser::parseHeadFromQStringGetSize(QString *text, int *size) {
    Q_ASSERT(text); Q_ASSERT(size);

    int iter = 0;

    QString sizeString = text->right(text->size() - 16 - 1);

    QString sizea;
    while (sizeString.length() > iter && sizeString.at(iter) != '_') {
        sizea.append(sizeString.at(iter++));
    }
    bool isOk;
    qDebug() << "DEBUG sizea = " << sizea;
    *size = sizea.toInt(&isOk);

    return isOk ? 0 : -1;
}

QString Parser::parseStringFromQDate(QDate *date) {
    Q_ASSERT(date);
    return date->toString(DATEFORMAT);
}

QString Parser::parseStringFromQDateTime(QDateTime *datetime) {
    Q_ASSERT(datetime);
    return datetime->toString(DATETIMEFORMAT);
}

QString Parser::parseStringFromSize(int size) {
    QString sizeBuff = QString::number(size);
    while (sizeBuff.size() < 6) {
        sizeBuff.push_front('0');
    }
    return sizeBuff;
}

QString Parser::generateHead(QDateTime *datetime, int size) {
    QString text;
    text.append(parseStringFromQDateTime(datetime));
    text.append('_');
    text.append(parseStringFromSize(size));
    text.append('_');
    return text;
}
