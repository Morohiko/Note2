#include "core.h"
#include "utils.h"
#include "file.h"

#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QString>

//int performWriteToFile(QString text) {
//    if (text.size() < 1) {
//        qDebug() << "ERROR: performWriteToFile: text is empty";

//        return -1;
//    }

//    QString finalText;
//    QString currentTime = getCurrentDateTime();

//    finalText.append(currentTime + '_');

//    int size = SIZE_OF_HEADER + text.size();

//    QString sizeBuff = QString::number(size);
//    while (sizeBuff.size() < 6) {
//        sizeBuff.push_front('0');
//    }

//    finalText.append(sizeBuff + '_' + text);

//    if (qWriteToEndFile(finalText)) {
//        qDebug() << "ERROR Cannot write to file";
//        return -1;
//    }

//    return 0;
//}

//QString performReadFromFile() {
//    QString text = qReadFromFile();
//    return text;
//}

//// return position or negative value in case error
//static int findPositionByHeader(int pos, QString header) {
//    QString headerTmp;
//    int size = 0;

//    do {
//        headerTmp = qReadFromFileByPosition(pos, SIZE_OF_HEADER);

//        if (headerTmp == nullptr) {
//            qDebug() << "ERROR findPositionByHeader not found";
//            return -1;
//        }

//        if (header != headerTmp) {
//            parseHeadFromQStringGetSize(&headerTmp, &size);
//            pos += size;
//        }

//        if (header == headerTmp) {
//            return pos;
//        }
//    } while (true);
//}

//// return position or negative value in case error
//static int findPositionByDate(int pos, QString date) {
//    QString headerTmp;
//    int size = 0;
//    QString dateBuff;

//    do {
//        headerTmp = qReadFromFileByPosition(pos, SIZE_OF_HEADER);

//        if (headerTmp == nullptr) {
//            qDebug() << "ERROR findPositionByDateheader not found";
//            return -1;
//        }

//        parseHeadFromQStringGetDateString(&headerTmp, &dateBuff);

//        qDebug() << "DEBUG: dateBuff = " << dateBuff << "date:" << dateBuff;
//        if (date != dateBuff) {
//            parseHeadFromQStringGetSize(&headerTmp, &size);
//            pos += size;
//        }

//        if (date == dateBuff) {
//            return pos;
//        }
//    } while (true);
//}

//// return body, nullptr in case error
//QString performReadBodyByHead(QString head) {
//    int pos = 0;
//    int size = 0;

//    pos = findPositionByHeader(pos, head);
//    if (pos < 0) {
//        qDebug() << "ERROR not found " << pos;
//        return nullptr;
//    }

//    parseHeadFromQStringGetSize(&head, &size);

//    pos += SIZE_OF_HEADER;
//    size -= SIZE_OF_HEADER;

//    return qReadFromFileByPosition(pos, size);
//}

//// return the number of successfully read datetime
//int performReadAllDatetime(QList<QDateTime *> *dateTimeList) {
//    if (dateTimeList == nullptr) {
//        qDebug() << "ERROR QList<QDateTime *> *dateTimeList is nullptr";
//        return 0;
//    }
//    int pos = 0; int size = 0; int count = 0;
//    QString buff;
//    QDateTime datetime;

//    do {
//        buff = qReadFromFileByPosition(pos, SIZE_OF_HEADER);

//        if (buff == nullptr) {
//            break;
//        }

//        if (parseHeadFromQString(&buff, &datetime, &size)) {
//            qDebug() << "ERROR cannot parse qstring in performReadAllDatetime";
//            break;
//        }

//        dateTimeList->append(new QDateTime(datetime));

//        pos += size;
//        count++;
//    } while (true);
//    return count;
//}

//int performReadByDateTime(QDateTime *datetime, QString *text) {
//    QDate date = datetime->date();
//    QString dateString = date.toString("yyyy/MM/dd");
//    qDebug() << "DEBUG: performReadByDateTime dateString = " << dateString;
//    int pos = 0; QString head;
//    QString body;
//    while (true) {
//        pos = findPositionByDate(pos, dateString);
//        qDebug() << "ERROR: pos = " << pos;

//        if (pos == -1) {
//            qDebug() << "ERROR: pos==-1";
//            return -1;
//        }
//        qDebug() << "DEBUG: ` pos:" << pos;
//        head = qReadFromFileByPosition(pos, SIZE_OF_HEADER);
//        body = performReadBodyByHead(head);
//        (*text).append(body + '\n');
//        pos += body.size() + SIZE_OF_HEADER;
//    }
//    return 0;
//}
