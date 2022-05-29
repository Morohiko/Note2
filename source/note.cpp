#include <cassert>
#include <iostream>

#include "note.h"
#include "log.h"

Note::Note() {
    note = this;
}

#ifdef USE_QT
int Note::setFilenameHandler(QString &filename) {
    WLOG(LOG_INFO, nullptr, nullptr);
    std::string filename_std = filename.toStdString();
    return note->setFilename(filename_std);
}

int Note::performReadByDateHandler(QDate &date, QString &key, QString &outputBody) {
    assert(note);
    WLOG(LOG_INFO, nullptr, nullptr);
    tm date_tm;
    int retval;

    date_tm.tm_year = date.year();
    date_tm.tm_mon = date.month();
    date_tm.tm_mday = date.day();
    std::wstring textStd;
    std::wstring keyStd = key.toStdWString();
    retval = note->performReadByDate(date_tm, keyStd, textStd);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cant perform read by date");
    }
    outputBody = QString::fromStdWString(textStd);
    return STATUS_SUCCESS;
}

int Note::performReadAllDateHandler(QString &key, QList<QDate *> &dateList) {
    assert(note);
    WLOG(LOG_INFO, nullptr, nullptr);
    std::list<std::wstring> list;
    std::wstring stdKey = key.toStdWString();
    int retval = note->performReadAllDate(stdKey, list);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cant read all date from file");
        return STATUS_FAILURE;
    }
    std::list<std::wstring>::iterator it;
    for (it = list.begin(); it != list.end(); ++it){
        QString qstring = QString::fromStdWString(*it);
        QDate *qdate = new QDate(QDate::fromString(qstring, QString("yyyy/M/dd")));
        dateList.append(qdate);
    }
    return STATUS_SUCCESS;
}

int Note::performWriteToFileHandler(QString &text, bool isCustomTime, QDateTime &datetime, QString &key) {
    assert(note);
    WLOG(LOG_INFO, nullptr, nullptr);
    std::wstring stdText = text.toStdWString();
    std::wstring stdKey = key.toStdWString();
    tm date_time_tm;
    date_time_tm.tm_year = datetime.date().year();
    date_time_tm.tm_mon = datetime.date().month();
    date_time_tm.tm_mday = datetime.date().day();
    date_time_tm.tm_hour = datetime.time().hour();
    date_time_tm.tm_min = datetime.time().minute();
    date_time_tm.tm_sec = datetime.time().second();
    return note->performWriteToFile(stdText, isCustomTime, date_time_tm, stdKey);
}
#endif

#ifdef USE_ANDROID
// TODO: android api
#endif

#ifdef USE_DUMMY
int Note::setFilenameHandler(std::string &filename) {
    assert(note);
    WLOG(LOG_INFO, nullptr, nullptr);
    return note->setFilename(filename);
}

int Note::performReadByDateHandler(tm &date, std::wstring &key, std::wstring &outputBody) {
    assert(note);
    WLOG(LOG_INFO, nullptr, nullptr);
    return note->performReadByDate(date, key, outputBody);
}

int Note::performReadAllDateHandler(std::wstring &key, std::list<std::wstring> &dateList) {
    assert(note);
    WLOG(LOG_INFO, nullptr, nullptr);
    return note->performReadAllDate(key, dateList);
}

int Note::performWriteToFileHandler(std::wstring &text, bool isCustomTime, tm &datetime, std::wstring &key) {
    assert(note);
    WLOG(LOG_INFO, nullptr, nullptr);
    return note->performWriteToFile(text, isCustomTime, datetime, key);
}
#endif

/**
 * @brief save filename of file for read/write data
 *
 * @param[in] filename name of file
 * 
 * @return execution status
 */
int Note::setFilename(std::string &filename) {
    WLOG(LOG_INFO, "save file for read write data");
    int retval = file.setPathToFile(filename);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cant set filename");
    }
    return retval;
}

/**
 * @brief write text to end of file
 *
 * @param[in] text data will be written to end of file
 * @param[in] isCustomTime check if use custom time or currentTime
 * @param[in] currentDateTime use customTime if isCustomTime is true
 * @param[in] key using for encode text before write to file
 * 
 * @return execution status
 */
int Note::performWriteToFile(std::wstring &text, bool isCustomTime, tm &customDateTime, std::wstring &key) {
    std::wstring datetimeStr, head, finalText;
    int retval;
    
    if (_isValidKey(key) == false) {
        WLOG(LOG_ERROR, "performWriteToFile isValidKey() == false");
        return STATUS_FAILURE;
    }

    if (isCustomTime) {
        datetime.updateToCustomDateTime(customDateTime);
    } else {
        datetime.updateToCurrentDateTime();
    }

    int size = SIZE_OF_HEADER + text.size();
    
    retval = datetime.getCurrentDateTimeString(datetimeStr);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cant get current datetime string");
        return STATUS_FAILURE;
    }
    retval = parser.generateHead(datetimeStr, size, head);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cant generate head");
        return STATUS_FAILURE;
    }

#ifdef WITH_ENCODER
    std::wstring decodedHead;
    retval = encoder.encodeStringByKey(head, key, decodedHead);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cannot encode head");
        return STATUS_FAILURE;
    }
    finalText.append(decodedHead);
#else
    finalText.append(head);
#endif

#ifdef WITH_ENCODER
    std::wstring decodedText;
    retval = encoder.encodeStringByKey(text, key, decodedText);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cannot encode text");
        return STATUS_FAILURE;
    }
    finalText.append(decodedText);
#else
    finalText.append(text);
#endif

    retval = file.writeToEndFile(finalText);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "Cannot write to file");
        return STATUS_FAILURE;
    }

    return STATUS_SUCCESS;
}

/**
 * @brief find position of head in file
 *
 * @param[in] head head wich will be find
 * @param[in] key using for decode data from file
 * @param[out] pos container which will save position of head in file
 * 
 * @return execution status
 */
int Note::_findPositionByHeader(std::wstring &head, std::wstring &key, int &pos) {
    int size = 0;
    do {
        std::wstring headerTmp;
        int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, headerTmp);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "retval = ", retval);
            break;
        }
#ifdef WITH_ENCODER
        std::wstring decodedHeaderTmp;
        retval = encoder.decodeStringByKey(headerTmp, key, decodedHeaderTmp);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant decode header");
            return STATUS_FAILURE;
        }
        headerTmp.clear();
        headerTmp.append(decodedHeaderTmp);
#endif
        if (headerTmp.empty()) {
            WLOG(LOG_ERROR, "header decoded string is empty");
            return STATUS_FAILURE;
        }
        
        if (head.compare(headerTmp) == 0) {
            WLOG(LOG_INFO, "found header by position");
            return STATUS_SUCCESS;
        }

        retval = parser.parseHeadFromStringGetSize(headerTmp, size);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant get size from head");
            return STATUS_FAILURE;
        }
        pos += size;
    } while (true);

    // cant be reached there
    return STATUS_SUCCESS;
}

/**
 * @brief find position of date in file
 *
 * @param[in] date date wich will be find
 * @param[in] key using for decode data from file
 * @param[out] pos container which will save position of date in file
 * 
 * @return execution status
 */
int Note::_findPositionByDate(std::wstring &date, std::wstring &key, int &startPos, int &pos) {
    std::wstring dateBuff;
    int size = 0;
    pos = startPos;
    do {
        std::wstring headerTmp;
        int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, headerTmp);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_WARN, "cant find date: ", date);
            return retval;
        }
        if (retval == STATUS_FAILURE) {
            WLOG(LOG_ERROR, "cant find posinion, date: ", date);
            return retval;
        }
        if (headerTmp.empty()) {
            WLOG(LOG_ERROR, "not found");
            return STATUS_FAILURE;
        }

#ifdef WITH_ENCODER
        std::wstring decodedHeaderTmp;
        retval = encoder.decodeStringByKey(headerTmp, key, decodedHeaderTmp);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant decode header");
            return STATUS_FAILURE;
        }
        headerTmp.clear();
        headerTmp.append(decodedHeaderTmp);
#endif

        retval = parser.parseHeadFromStringGetDateString(headerTmp, dateBuff);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant parse date from head, retval: ", retval);
            return retval;
        }

        if (date.compare(dateBuff) == 0) {
            WLOG(LOG_INFO, "found position by date");
            return STATUS_SUCCESS;
        }

        retval = parser.parseHeadFromStringGetSize(headerTmp, size);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant get size from head");
            return STATUS_FAILURE;
        }
        pos += size;
    } while (true);

    // cant be reached there
    return STATUS_SUCCESS;
}

/**
 * @brief check if key compares with file
 *
 * @param[in] key
 * 
 * @return true if key is valid, false otherwise
 */
bool Note::_isValidKey(std::wstring &key) {
    std::wstring buff;
    int pos = 0; int size;
    std::wstring date_str;
    if (file.isCurrentFileEmpty()) {
        WLOG(LOG_ERROR, "file is empty");
        return true;
    }
    int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, buff);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "isValidKey/readFromFileByPosition: retval = ", retval);
        return STATUS_FAILURE;
    }

#ifdef WITH_ENCODER
    std::wstring decudedBuff;
    retval = encoder.decodeStringByKey(buff, key, decudedBuff);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cant decode key");
        return false;
    }
    buff.clear();
    buff.append(decudedBuff);
#endif
    retval = parser.parseHeadFromString(buff, date_str, size);
    if (retval == STATUS_END_OF_FILE || retval == STATUS_SUCCESS) {
        return true;
    }
    return false;
}

/**
 * @brief read add date from file
 *
 * @param[in] key using for decode data from file
 * @param[out] dateList container with read dates
 * 
 * @return execution status
 */
int Note::performReadAllDate(std::wstring &key, std::list<std::wstring> &dateList) {
    int pos = 0; int size = 0;
    std::wstring buff;
    std::wstring date;
    int retval;

    do {
        buff.clear();
        retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, buff);
        if (retval == STATUS_END_OF_FILE) {
            WLOG(LOG_WARN, "performReadAllDate end of file");
            return STATUS_SUCCESS;
        }
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "performReadAllDate failure");
        }
#ifdef WITH_ENCODER
        std::wstring decodedBuff;
        retval = encoder.decodeStringByKey(buff, key, decodedBuff);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant decode buffer when read all date");
            return STATUS_FAILURE;
        }
        buff.clear();
        buff.append(decodedBuff);
#endif
        retval = parser.parseHeadFromString(buff, date, size);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "parser.parseHeadFromString retval = ", retval);
            break;
        }
        WLOG(LOG_DEBUG, "dateList push_back: date = ", date);
        dateList.push_back(date);
        pos += size;
    } while (true);
    return retval;
}

/**
 * @brief read body from file, with incoming date
 *
 * @param[in] date read body with this date
 * @param[in] key using for decode data from file
 * @param[out] outputBody readded body from file
 * 
 * @return execution status
 */
int Note::performReadByDate(tm &date, std::wstring &key, std::wstring &outputBody) {
    int pos = 0;
    int retval;
    int size = 0;
    std::wstring head;
    std::wstring time;
    std::wstring body;
    std::wstring dateString;

    outputBody.clear();

    retval = datetime.convertTmDateToString(date, dateString);
    if (retval != STATUS_SUCCESS) {
        WLOG(LOG_ERROR, "cant convert tm to string");
        return STATUS_FAILURE;
    }

    while (true) {
        retval = _findPositionByDate(dateString, key, pos, pos);
        if (retval == STATUS_END_OF_FILE) {
            WLOG(LOG_INFO, "end of file");
            retval = STATUS_SUCCESS;
            break;
        }

        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cand find position by date");
            return STATUS_FAILURE;
        }

        // read head
        retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, head);
        if (retval == STATUS_END_OF_FILE) {
            WLOG(LOG_INFO, "end of file");
            retval = STATUS_SUCCESS;
            break;
        }
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant read from file by position: retval = ", retval);
        }
    #ifdef WITH_ENCODER
        std::wstring decodedHead;
        retval = encoder.decodeStringByKey(head, key, decodedHead);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant decode body");
            return STATUS_FAILURE;
        }
        head = decodedHead;
    #endif

        retval = parser.parseHeadFromStringGetSize(head, size);
        if (retval != STATUS_SUCCESS) {
            return STATUS_FAILURE;
        }

        pos += SIZE_OF_HEADER;
        size -= SIZE_OF_HEADER;

        retval = file.readFromFileByPosition(pos, size, body);
        if (retval == STATUS_END_OF_FILE) {
            retval = STATUS_SUCCESS;
            break;
        }
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant read from file by position");
            return retval;
        }

#ifdef WITH_ENCODER
        std::wstring decodedBody;
        retval = encoder.decodeStringByKey(body, key, decodedBody);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant decode body");
            return STATUS_FAILURE;
        }
        body = decodedBody;
#endif

        retval = parser.parseHeadFromStringGetTimeString(head, time);
        if (retval != STATUS_SUCCESS) {
            WLOG(LOG_ERROR, "cant parse time from head");
            return retval;
        }

        pos += size;
        outputBody.append(time + L'\n' + body + L"\n\n");
    }
    return retval;
}
