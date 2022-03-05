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

int Note::performReadByDateHandler(QDate *date, QString *text, QString *key) {
    assert(note);
    std::wcout << LOG_DEBUG << std::endl;
    tm date_tm;
    date_tm.tm_year = date->year();
    date_tm.tm_mon = date->month();
    date_tm.tm_mday = date->day();
    std::wstring textStd = text->toStdWString();
    std::wstring keyStd = key->toStdWString();
    int count = note->performReadByDate(date_tm, textStd, keyStd);
    *text = QString::fromStdWString(textStd);
    return 0;
}

int Note::performReadAllDateHandler(QList<QDate *> *dateList, QString *key) {
    assert(note); assert(dateList); assert(key);
    std::wcout << LOG_DEBUG << std::endl;
    std::list<std::wstring> list;
    std::wstring stdKey = key->toStdWString();
    int count = note->performReadAllDate(list, stdKey);
    std::list<std::wstring>::iterator it;
    for (it = list.begin(); it != list.end(); ++it){
        QString qstring = QString::fromStdWString(*it);
        QDate *qdate = new QDate(QDate::fromString(qstring, QString("yyyy/M/dd")));
        dateList->append(qdate);
    }
    return count;
}

int Note::performWriteToFileHandler(QString *text, bool isCustomTime, QDateTime *datetime, QString *key) {
    assert(note);
    std::wcout << LOG_DEBUG << std::endl;
    std::wstring stdText = text->toStdWString();
    std::wstring stdKey = key->toStdWString();
    tm date_time_tm;
    date_time_tm.tm_year = datetime->date().year();
    date_time_tm.tm_mon = datetime->date().month();
    date_time_tm.tm_mday = datetime->date().day();
    date_time_tm.tm_hour = datetime->time().hour();
    date_time_tm.tm_min = datetime->time().minute();
    date_time_tm.tm_sec = datetime->time().second();
    return note->performWriteToFile(stdText, isCustomTime, date_time_tm, stdKey);
}
#endif

#ifdef USE_ANDROID
// TODO: android api
#endif

#ifdef USE_DUMMY
int Note::setFilenameHandler(std::string *filename) {
    assert(note); assert(filename);
    return note->setFilename(*filename);
}

int Note::performReadByDateHandler(tm *date, std::wstring *text, std::wstring *key) {
    assert(note); assert(date);
    assert(text); assert(key);
    return note->performReadByDate(*date, *text, *key);
}

int Note::performReadAllDateHandler(std::list<std::wstring> *dateList, std::wstring *key) {
    assert(note); assert(dateList); assert(key);
    return note->performReadAllDate(*dateList, *key);
}

int Note::performWriteToFileHandler(std::wstring *text, bool isCustomTime, tm *datetime, std::wstring *key) {
    assert(note); assert(text);
    assert(datetime); assert(key);
    return note->performWriteToFile(*text, isCustomTime, *datetime, *key);
}
#endif

int Note::setFilename(std::string &filename) {
    int retval = file.setPathToFile(filename);
    if (retval != STATUS_SUCCESS) {
        std::cout << LOG_ERROR << "cant set filename: filename = " << filename << std::endl;
    }
    return retval;
}

#ifdef WITH_ENCODER
std::wstring Note::performEncodeString(std::wstring &text, std::wstring &key) {
    std::wstring dest;
    if (key.size() == 0) {
        std::wcout << LOG_ERROR << "key.size() == 0" << std::endl;
        return dest;
    }
    return encoder.encodeStringByKey(text, key);
}

std::wstring Note::performDecodeString(std::wstring &text, std::wstring &key) {
    std::wstring dest;
    if (key.size() == 0) {
        std::wcout << LOG_ERROR << "key.size() == 0" << std::endl;
        return dest;
    }
    return encoder.decodeStringByKey(text, key);
}
#endif

int Note::performWriteToFile(std::wstring &text, bool isCustomTime, tm &currentDateTime, std::wstring &key) {
    if (isValidKey(key) == false) {
        std::wcout << LOG_ERROR << "performWriteToFile isValidKey() == false" << std::endl;
        return -1;
    }

    std::wstring finalText;

    if (isCustomTime) {
        datetime.updateToCustomDateTime(currentDateTime);
    } else {
        datetime.updateToCurrentDateTime();
    }

    int size = SIZE_OF_HEADER + text.size();
    std::wstring datetime_str = datetime.getCurrentDateTimeString();
    std::wstring head = parser.generateHead(datetime_str, size);

#ifdef WITH_ENCODER
    head = performEncodeString(head, key);
#endif
    finalText.append(head);

#ifdef WITH_ENCODER
    text = performEncodeString(text, key);
#endif
    finalText.append(text);

    if (file.writeToEndFile(finalText)) {
        std::wcout << LOG_ERROR << "Cannot write to file" << std::endl;
        return -1;
    }

    return 0;
}

// return position or negative value in case error
int Note::findPositionByHeader(int pos, std::wstring &header, std::wstring &key) {
    int size = 0;
    do {
        std::wstring headerTmp;
        int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, headerTmp);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "retval = " << retval << std::endl;
            break;
        }
#ifdef WITH_ENCODER
        headerTmp = performDecodeString(headerTmp, key);
#endif
        if (headerTmp.empty()) {
            std::wcout << LOG_ERROR << "not found" << std::endl;
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

int Note::findPositionByDate(int &pos /*output*/, std::wstring &date, std::wstring &key) {
    std::wstring dateBuff;
    int size = 0;
    do {
        std::wstring headerTmp;
        int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, headerTmp);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_WARN << "cant file date: " << date << std::endl;
            return retval;
        }
        if (retval == STATUS_FAILURE) {
            std::wcout << LOG_ERROR << "cant file posinion, date: " << date << std::endl;
            return retval;
        }
        if (headerTmp.empty()) {
            std::wcout << LOG_ERROR << "not found" << std::endl;
            return -1;
        }

#ifdef WITH_ENCODER
        headerTmp = performDecodeString(headerTmp, key);
#endif

        retval = parser.parseHeadFromStringGetDateString(headerTmp, dateBuff);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "cant parse date from head, retval: " << retval << std::endl;
        }

        if (date != dateBuff) {
            parser.parseHeadFromStringGetSize(headerTmp, size);
            pos += size;
        }

        if (date.compare(dateBuff) == 0) {
            return STATUS_SUCCESS;
        }
    } while (true);
}

int Note::performReadBodyByHead(std::wstring &head, std::wstring &ouptut, std::wstring &key) {
    int pos = 0;
    int size = 0;

    pos = findPositionByHeader(pos, head, key);
    if (pos < 0) {
        std::wcout << LOG_ERROR << "not found " << pos << std::endl;
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
        std::wcout << LOG_ERROR << "is not working" << std::endl;
        return retval;
    }

#ifdef WITH_ENCODER
    ouptut = performDecodeString(ouptut, key);
#endif

    return retval;
}

bool Note::isValidKey(std::wstring &key) {
    std::wstring buff;
    int pos = 0; int size;
    std::wstring date_str;
    if (file.isCurrentFileEmpty()) {
        std::wcout << LOG_ERROR << "file is empty" << std::endl;
        return true;
    }
    int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, buff);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "isValidKey/readFromFileByPosition: retval = " << retval << std::endl;
        return STATUS_FAILURE;
    }

#ifdef WITH_ENCODER
    buff = performDecodeString(buff, key);
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
int Note::performReadAllDate(std::list<std::wstring> &dateList, std::wstring &key) {
    int pos = 0; int size = 0; int count = 0;
    std::wstring buff;
    std::wstring date;
    int retval;
    int state = 0;

    do {
        buff.clear();
        retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, buff);
        if (retval == STATUS_END_OF_FILE) {
            std::wcout << LOG_WARN << "performReadAllDate end of file buff = " << buff << std::endl;
            state = retval;
            break;
        }
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "performReadAllDate failure" << std::endl;
        }
#ifdef WITH_ENCODER
        buff = performDecodeString(buff, key);
#endif
        retval = parser.parseHeadFromString(buff, date, size);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "parser.parseHeadFromString retval = " << retval << std::endl;
            break;
        }
        std::wcout << LOG_DEBUG << "dateList push_back: date = " << date << std::endl;
        dateList.push_back(date);
        pos += size;
        count++;
    } while (state != STATUS_END_OF_FILE);
    return count;
}

int Note::performReadByDate(tm &date, std::wstring &text, std::wstring &key) {
    std::wstring dateString = datetime.convertTmDateToString(date);

    int pos = 0;
    int returnedPosition = 0;
    std::wstring head;
    std::wstring time;
    std::wstring body;
    bool found = false;
    int retval = findPositionByDate(pos, dateString, key);

    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "failure on find position" << std::endl;
        return retval;
    }
    std::wcout << LOG_DEBUG << "date found" << std::endl;
    retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, head);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "retval = " << retval << std::endl;
        return retval;
    }
#ifdef WITH_ENCODER
    head = performDecodeString(head, key);
#endif
    parser.parseHeadFromStringGetTimeString(head, time);
    retval = performReadBodyByHead(head, body, key);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "failure on read body" << std::endl;
        return retval;
    }
    text.append(time + L'\n' + body + L"\n\n");
    return STATUS_SUCCESS;
}
