#include <cassert>
#include <iostream>

#include "note.h"

Note::Note() {
    note = this;
}

#ifdef USE_QT
int Note::setFilenameHandler(QString *filename) {
    std::string filename_std = filename->toStdString();
    return note->setFilename(filename_std);
}

int Note::performReadByDateHandler(QDate *date, QString *text) {
    assert(note);
    std::cout << LOG_DEBUG << std::endl;
    tm date_tm;
    date_tm.tm_year = date->year();
    date_tm.tm_mon = date->month();
    date_tm.tm_mday = date->day();
    std::string text_std = text->toStdString();
    int count = note->performReadByDate(&date_tm, &text_std);
    *text = QString::fromStdString(text_std);
    return 0;
}

int Note::performReadAllDateHandler(QList<QDate *> *dateList) {
    assert(note);
    std::cout << LOG_DEBUG << std::endl;
    std::list<std::string> list;
    int count = note->performReadAllDate(&list);
    std::list<std::string>::iterator it;
    for (it = list.begin(); it != list.end(); ++it){
        QString qstring = QString::fromStdString(*it);
        QDate *qdate = new QDate(QDate::fromString(qstring, QString("yyyy/M/dd")));
        dateList->append(qdate);
    }
    return count;
}

int Note::performWriteToFileHandler(QString *text, bool isCustomTime, QDateTime *datetime) {
    assert(note);
    std::cout << LOG_DEBUG << std::endl;
    std::string stdText = text->toStdString();
    tm date_time_tm;
    date_time_tm.tm_year = datetime->date().year();
    date_time_tm.tm_mon = datetime->date().month();
    date_time_tm.tm_mday = datetime->date().day();
    date_time_tm.tm_hour = datetime->time().hour();
    date_time_tm.tm_min = datetime->time().minute();
    date_time_tm.tm_sec = datetime->time().second();
    return note->performWriteToFile(stdText, isCustomTime, &date_time_tm);
}
#endif

#ifdef USE_ANDROID
// TODO: android api
#endif

#ifdef USE_DUMMY
int Note::setFilenameHandler(std::string filename) {
    assert(note);
    return note->setFilename(filename);
}

int Note::performReadByDateHandler(tm *date, std::string *text) {
    assert(note);
    return note->performReadByDate(date, text);
}

int Note::performReadAllDateHandler(std::list<std::string> *dateList) {
    assert(note);
    return note->performReadAllDate(dateList);
}

int Note::performWriteToFileHandler(std::string *text, bool isCustomTime, tm *datetime) {
    assert(note);
    return note->performWriteToFile(*text, isCustomTime, datetime);
}
#endif

int Note::setFilename(std::string filename) {
    int retval = file.setPathToFile(filename);
    if (retval != STATUS_SUCCESS) {
        std::cout << LOG_ERROR << "cant set filename: filename = " << filename << std::endl;
    }
    return retval;
}

#ifdef WITH_ENCODER
std::string Note::performEncodeString(std::string *text) {
    std::string key = window.getKey();
    std::string dest;
    dest.append(text);
    if (key.size() > 0) {
        dest = encoder.encodeStringByKey(&dest, &key);
    }
    return dest;
}

std::string Note::performDecodeString(std::string *text) {
    std::string key = window.getKey();
    std::string dest;
    dest.append(text);
    if (key.size() > 0) {
        dest = encoder.decodeStringByKey(&dest, &key);
    }
    return dest;
}
#endif

int Note::performWriteToFile(std::string text, bool isCustomTime, tm* currentDateTime) {
    if (isValidKey() == false) {
        std::cout << LOG_ERROR << "performWriteToFile isValidKey() == false" << std::endl;
        return -1;
    }

    std::string finalText;

    if (isCustomTime) {
        datetime.updateToCustomDateTime(currentDateTime);
    } else {
        datetime.updateToCurrentDateTime();
    }

    int size = SIZE_OF_HEADER + text.size();
    std::string datetime_str = datetime.getCurrentDateTimeString();
    std::string head = parser.generateHead(datetime_str, size);

#ifdef WITH_ENCODER
    head = performEncodeString(&head);
#endif
    finalText.append(head);

#ifdef WITH_ENCODER
    text = performEncodeString(&text);
#endif
    finalText.append(text);

    if (file.writeToEndFile(finalText)) {
        std::cout << LOG_ERROR << "Cannot write to file" << std::endl;
        return -1;
    }

    return 0;
}

// return position or negative value in case error
int Note::findPositionByHeader(int pos, std::string header) {
    int size = 0;

    do {
        std::string headerTmp;
        int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, headerTmp);
        if (retval != STATUS_SUCCESS) {
            std::cout << LOG_ERROR << "retval = " << retval << std::endl;
            break;
        }
#ifdef WITH_ENCODER
        headerTmp = performDecodeString(&headerTmp);
#endif
        if (headerTmp.empty()) {
            std::cout << LOG_ERROR << "not found" << std::endl;
            return -1;
        }

        if (header != headerTmp) {
            parser.parseHeadFromStringGetSize(headerTmp, size);
            pos += size;
        }

        if (header == headerTmp) {
            return pos;
        }
    } while (true);

    // cant be reached there
    return STATUS_SUCCESS;
}

int Note::findPositionByDate(int pos, std::string date, int &returnPosition) {
    std::string dateBuff;
    int size = 0;

    do {
        std::string headerTmp;
        int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, headerTmp);
        if (retval != STATUS_SUCCESS) {
            std::cout << LOG_WARN << "cant file date: " << date << std::endl;
            return retval;
        }
        if (retval == STATUS_FAILURE) {
            std::cout << LOG_ERROR << "cant file posinion, date: " << date << std::endl;
            return retval;
        }
        if (headerTmp.empty()) {
            std::cout << LOG_ERROR << "not found" << std::endl;
            return -1;
        }

#ifdef WITH_ENCODER
        headerTmp = performDecodeString(&headerTmp);
#endif

        retval = parser.parseHeadFromStringGetDateString(headerTmp, dateBuff);
        if (retval != STATUS_SUCCESS) {
            std::cout << LOG_ERROR << "cant parse date from head, retval: " << retval << std::endl;
        }

        if (date != dateBuff) {
            parser.parseHeadFromStringGetSize(headerTmp, size);
            pos += size;
        }

        if (date == dateBuff) {
            return pos;
        }
    } while (true);
}

int Note::performReadBodyByHead(std::string head, std::string &ouptut) {
    std::cout << LOG_DEBUG << "head = " << head << std::endl;
    int pos = 0;
    int size = 0;

    pos = findPositionByHeader(pos, head);
    if (pos < 0) {
        std::cout << LOG_ERROR << "not found " << pos << std::endl;
        return STATUS_FAILURE;
    }

    int stat = parser.parseHeadFromStringGetSize(head, size);
    if (stat == -1) {
        return STATUS_FAILURE;
    }

    pos += SIZE_OF_HEADER;
    size -= SIZE_OF_HEADER;

    int retval = file.readFromFileByPosition(pos, size, ouptut);
    if (retval != STATUS_SUCCESS) {
        std::cout << LOG_ERROR << "is not working" << std::endl;
        return retval;
    }

#ifdef WITH_ENCODER
    ouptut = performDecodeString(&ouptut);
#endif

    return retval;
}

bool Note::isValidKey() {
    std::string buff;
    int pos = 0; int size;
    std::string date_str;
    if (file.isCurrentFileEmpty()) {
        std::cout << LOG_ERROR << "file is empty" << std::endl;
        return true;
    }
    int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, buff);
    if (retval != STATUS_SUCCESS) {
        std::cout << LOG_ERROR << "isValidKey/readFromFileByPosition: retval = " << retval << std::endl;
        return STATUS_FAILURE;
    }
#ifdef WITH_ENCODER
    buff = performDecodeString(&buff);
#endif
    retval = parser.parseHeadFromString(buff, date_str, size);
    if (retval == STATUS_END_OF_FILE) {
        return true;
    } else if (retval == 0) {
        return true;
    } else {
        return false;
    }
}

// return the number of successfully read datetime
int Note::performReadAllDate(std::list<std::string> *dateList) {
    assert(dateList);

    int pos = 0; int size = 0; int count = 0;
    std::string buff;
    std::string date;
    int retval;
    int state = 0;

    do {
        buff.clear();
        retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, buff);
        if (retval == STATUS_END_OF_FILE) {
            std::cout << LOG_WARN << "performReadAllDate end of file buff = " << buff << std::endl;
            state = retval;
            break;
        }
        if (retval != STATUS_SUCCESS) {
            std::cout << LOG_ERROR << "performReadAllDate failure" << std::endl;
        }
#ifdef WITH_ENCODER
        buff = performDecodeString(&buff);
#endif
        retval = parser.parseHeadFromString(buff, date, size);
        std::cout << LOG_DEBUG << "buf = " << buff << ", date = " << date << ", size = " << size << std::endl;
        if (retval != STATUS_SUCCESS) {
            std::cout << LOG_ERROR << "parser.parseHeadFromString retval = " << retval << std::endl;
            break;
        }
        std::cout << LOG_DEBUG << "dateList push_back: date = " << date << std::endl;
        dateList->push_back(date);
        pos += size;
        count++;
    } while (state != STATUS_END_OF_FILE);
    return count;
}

int Note::performReadByDate(tm *date, std::string *text) {
    assert(date); assert(text);

    std::string dateString = datetime.convertTmDateToString(date);

    int pos = 0;
    int returnedPosition = 0;
    std::string head;
    std::string time;
    std::string body;
    while (true) {
        int retval = findPositionByDate(pos, dateString, returnedPosition);
        if (retval == STATUS_END_OF_FILE) {
            std::cout << LOG_WARN << "End of file" << std::endl;
            break;
        }
        if (retval == STATUS_FAILURE) {
            std::cout << LOG_ERROR << "failure on find position" << std::endl;
        }
        pos = returnedPosition;
        retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, head);
        if (retval != STATUS_SUCCESS) {
            std::cout << LOG_ERROR << "retval = " << retval << std::endl;
            return retval;
        }
#ifdef WITH_ENCODER
        head = performDecodeString(&head);
#endif
        parser.parseHeadFromStringGetTimeString(head, time);
        retval = performReadBodyByHead(head, body);
        (*text).append(time + '\n' + body + "\n\n");
        pos += body.size() + SIZE_OF_HEADER;
    }
    return 0;
}
