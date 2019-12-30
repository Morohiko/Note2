#include "note.h"

#include <QDebug>

Note::Note() {
    note = this;
}

int Note::start() {
    window.setCallbacks(setFilenameHandler, performReadByDateHandler,
                        performReadAllDateHandler, performWriteToFileHandler);
    window.show();
    return 0;
}

void Note::setFilenameHandler(QString filename) {
    Q_ASSERT(note);
    return note->setFilename(filename);
}

int Note::performReadByDateHandler(QDate *date, QString *text) {
    Q_ASSERT(note);
    return note->performReadByDate(date, text);
}

int Note::performReadAllDateHandler(QList<QDate *> *dateList) {
    Q_ASSERT(note);
    return note->performReadAllDate(dateList);
}

int Note::performWriteToFileHandler(QString text) {
    Q_ASSERT(note);
    return note->performWriteToFile(text);
}

void Note::setFilename(QString filename) {
    file.setPathToFile(filename);
}

#ifdef WITH_ENCODER
QString Note::performEncodeString(QString *text) {
    QString key = window.getKey();
    QString dest;
    dest.append(text);
    if (key.size() > 0) {
        dest = encoder.encodeStringByKey(&dest, &key);
    }
    return dest;
}

QString Note::performDecodeString(QString *text) {
    QString key = window.getKey();
    QString dest;
    dest.append(text);
    if (key.size() > 0) {
        dest = encoder.decodeStringByKey(&dest, &key);
    }
    return dest;
}
#endif

int Note::performWriteToFile(QString text) {
    if (isValidKey() == false) {
        qDebug() << "performWriteToFile isValidKey() == false";
        return -1;
    }
    if (text.size() < 1) {
        qDebug() << "ERROR: performWriteToFile: text is empty";
        return -1;
    }

    QString finalText;
    QDateTime datetime;
    if (window.isCheckedCheckBoxCustomTime()) {
        datetime = window.getCustomDateTime();
    } else {
        datetime = QDateTime::currentDateTime();
    }

    int size = SIZE_OF_HEADER + text.size();
    QString head = parser.generateHead(&datetime, size);

#ifdef WITH_ENCODER
    head = performEncodeString(&head);
#endif
    finalText.append(head);

#ifdef WITH_ENCODER
    text = performEncodeString(&text);
#endif
    finalText.append(text);

    if (file.qWriteToEndFile(finalText)) {
        qDebug() << "ERROR Cannot write to file";
        return -1;
    }

    return 0;
}

// return position or negative value in case error
int Note::findPositionByHeader(int pos, QString header) {
    QString headerTmp;
    int size = 0;

    do {
        headerTmp = file.qReadFromFileByPosition(pos, SIZE_OF_HEADER);
#ifdef WITH_ENCODER
        headerTmp = performDecodeString(&headerTmp);
#endif
        if (headerTmp == nullptr) {
            qDebug() << "ERROR findPositionByHeader not found";
            return -1;
        }

        if (header != headerTmp) {
            parser.parseHeadFromQStringGetSize(&headerTmp, &size);
            qDebug() << "DEBUG: size = " << size;
            pos += size;
        }

        if (header == headerTmp) {
            return pos;
        }
    } while (true);
}

// return position or negative value in case error
int Note::findPositionByDate(int pos, QString date) {
    QString headerTmp;
    QString dateBuff;
    int size = 0;

    do {
        headerTmp = file.qReadFromFileByPosition(pos, SIZE_OF_HEADER);
#ifdef WITH_ENCODER
        headerTmp = performDecodeString(&headerTmp);
#endif
        if (headerTmp == nullptr) {
            qDebug() << "ERROR findPositionByDateheader not found";
            return -1;
        }

        qDebug() << "DEBUG headerTmp = " << headerTmp;
        parser.parseHeadFromQStringGetDateString(&headerTmp, &dateBuff);

        qDebug() << "DEBUG: dateBuff = " << dateBuff << "date:" << date;
        if (date != dateBuff) {
            parser.parseHeadFromQStringGetSize(&headerTmp, &size);
            pos += size;
        }

        if (date == dateBuff) {
            return pos;
        }
    } while (true);
}

// return body, nullptr in case error
QString Note::performReadBodyByHead(QString head) {
    int pos = 0;
    int size = 0;

    pos = findPositionByHeader(pos, head);
    if (pos < 0) {
        qDebug() << "ERROR not found " << pos;
        return nullptr;
    }

    parser.parseHeadFromQStringGetSize(&head, &size);

    pos += SIZE_OF_HEADER;
    size -= SIZE_OF_HEADER;

    QString text = file.qReadFromFileByPosition(pos, size);
    qDebug() << "DEBUG: performReadBodyByHead text" <<text;
#ifdef WITH_ENCODER
    text = performDecodeString(&text);
#endif
    return text;
}

bool Note::isValidKey() {
    QString buff;
    int pos = 0; int size;
    QDate date;
    buff = file.qReadFromFileByPosition(pos, SIZE_OF_HEADER);
#ifdef WITH_ENCODER
    buff = performDecodeString(&buff);
#endif
    if (buff == nullptr) {
//        qDebug() << "DEBUG is new key ";
        return true;
    }

    if (parser.parseHeadFromQString(&buff, &date, &size)) {
        qDebug() << "ERROR cannot parse qstring in performReadAllDatetime";
        return false;
    }
    return true;
}

// return the number of successfully read datetime
int Note::performReadAllDate(QList<QDate *> *dateList) {
    Q_ASSERT(dateList);

    int pos = 0; int size = 0; int count = 0;
    QString buff;
    QDate date;

    do {
        buff = file.qReadFromFileByPosition(pos, SIZE_OF_HEADER);
#ifdef WITH_ENCODER
        buff = performDecodeString(&buff);
#endif
        if (buff == nullptr) {
            break;
        }

        if (parser.parseHeadFromQString(&buff, &date, &size)) {
            qDebug() << "ERROR cannot parse qstring in performReadAllDatetime";
            break;
        }

        dateList->append(new QDate(date));

        pos += size;
        count++;
    } while (true);
    return count;
}

int Note::performReadByDate(QDate *date, QString *text) {
    Q_ASSERT(date); Q_ASSERT(text);

    QString dateString = parser.parseStringFromQDate(date);

    int pos = 0; QString head; QString time; QString body;
    while (true) {
        pos = findPositionByDate(pos, dateString);
        qDebug() << "ERROR: pos = " << pos;

        if (pos == -1) {
            qDebug() << "ERROR: pos==-1";
            break;
        }
        qDebug() << "DEBUG: performReadByDateTime pos:" << pos;
        head = file.qReadFromFileByPosition(pos, SIZE_OF_HEADER);
#ifdef WITH_ENCODER
        head = performDecodeString(&head);
#endif
        parser.parseHeadFromQStringGetTimeString(&head, &time);
        body = performReadBodyByHead(head);
        (*text).append(time + '\n' + body + "\n\n");
        pos += body.size() + SIZE_OF_HEADER;
    }
    return 0;
}
