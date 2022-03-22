#include <cassert>
#include <iostream>

#include "note.h"

Note::Note() {
    note = this;
}

#ifdef USE_QT
int Note::setFilenameHandler(QString &filename) {
    std::wcout << LOG_INFO << std::endl;
    std::string filename_std = filename.toStdString();
    return note->setFilename(filename_std);
}

int Note::performReadByDateHandler(QDate &date, QString &key, QString &outputBody) {
    assert(note);
    std::wcout << LOG_INFO << std::endl;
    tm date_tm;
    int retval;

    date_tm.tm_year = date.year();
    date_tm.tm_mon = date.month();
    date_tm.tm_mday = date.day();
    std::wstring textStd;
    std::wstring keyStd = key.toStdWString();
    retval = note->performReadByDate(date_tm, keyStd, textStd);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant perform read by date" << std::endl;
    }
    outputBody = QString::fromStdWString(textStd);
    return STATUS_SUCCESS;
}

int Note::performReadAllDateHandler(QString &key, QList<QDate *> &dateList) {
    assert(note);
    std::wcout << LOG_INFO << std::endl;
    std::list<std::wstring> list;
    std::wstring stdKey = key.toStdWString();
    int retval = note->performReadAllDate(stdKey, list);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant read all date from file" << std::endl;
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
    std::wcout << LOG_INFO << std::endl;
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
    std::wcout << LOG_INFO << std::endl;
    return note->setFilename(filename);
}

int Note::performReadByDateHandler(tm &date, std::wstring &key, std::wstring &outputBody) {
    assert(note);
    std::wcout << LOG_INFO << std::endl;
    return note->performReadByDate(date, key, outputBody);
}

int Note::performReadAllDateHandler(std::wstring &key, std::list<std::wstring> &dateList) {
    assert(note);
    std::wcout << LOG_INFO << std::endl;
    return note->performReadAllDate(key, dateList);
}

int Note::performWriteToFileHandler(std::wstring &text, bool isCustomTime, tm &datetime, std::wstring &key) {
    assert(note);
    std::wcout << LOG_INFO << std::endl;
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
    std::cout << LOG_INFO << "save file " << filename << " for read write data" << std::endl;
    int retval = file.setPathToFile(filename);
    if (retval != STATUS_SUCCESS) {
        std::cout << LOG_ERROR << "cant set filename: filename = " << filename << std::endl;
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
        std::wcout << LOG_ERROR << "performWriteToFile isValidKey() == false" << std::endl;
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
        std::wcout << LOG_ERROR << "cant get current datetime string" << std::endl;
        return STATUS_FAILURE;
    }
    retval = parser.generateHead(datetimeStr, size, head);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant generate head" << std::endl;
        return STATUS_FAILURE;
    }

#ifdef WITH_ENCODER
    std::wstring decodedHead;
    retval = encoder.encodeStringByKey(head, key, decodedHead);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cannot encode head" << std::endl;
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
        std::wcout << LOG_ERROR << "cannot encode text" << std::endl;
        return STATUS_FAILURE;
    }
    finalText.append(decodedText);
#else
    finalText.append(text);
#endif

    retval = file.writeToEndFile(finalText);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "Cannot write to file" << std::endl;
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
            std::wcout << LOG_ERROR << "retval = " << retval << std::endl;
            break;
        }
#ifdef WITH_ENCODER
        std::wstring decodedHeaderTmp;
        retval = encoder.decodeStringByKey(headerTmp, key, decodedHeaderTmp);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "cant decode header" << std::endl;
            return STATUS_FAILURE;
        }
        headerTmp.clear();
        headerTmp.append(decodedHeaderTmp);
#endif
        if (headerTmp.empty()) {
            std::wcout << LOG_ERROR << "header decoded string is empty" << std::endl;
            return STATUS_FAILURE;
        }
        
        if (head.compare(headerTmp) == 0) {
            std::wcout << LOG_INFO << "found header by position" << std::endl;
            return STATUS_SUCCESS;
        }

        retval = parser.parseHeadFromStringGetSize(headerTmp, size);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "cant get size from head" << std::endl;
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
int Note::_findPositionByDate(std::wstring &date, std::wstring &key, int &pos) {
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
            return STATUS_FAILURE;
        }

#ifdef WITH_ENCODER
        std::wstring decodedHeaderTmp;
        retval = encoder.decodeStringByKey(headerTmp, key, decodedHeaderTmp);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "cant decode header" << std::endl;
            return STATUS_FAILURE;
        }
        headerTmp.clear();
        headerTmp.append(decodedHeaderTmp);
#endif

        retval = parser.parseHeadFromStringGetDateString(headerTmp, dateBuff);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "cant parse date from head, retval: " << retval << std::endl;
            return retval;
        }

        if (date.compare(dateBuff) == 0) {
            std::wcout << LOG_INFO << "found position by date" << std::endl;
            return STATUS_SUCCESS;
        }

        retval = parser.parseHeadFromStringGetSize(headerTmp, size);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "cant get size from head" << std::endl;
            return STATUS_FAILURE;
        }
        pos += size;
    } while (true);

    // cant be reached there
    return STATUS_SUCCESS;
}

/**
 * @brief read body with head
 *
 * @param[in] head body whit this head will be read
 * @param[in] key using for decode data from file
 * @param[out] output container which will save body
 * 
 * @return execution status
 */
int Note::_performReadBodyByHead(std::wstring &head, std::wstring &key, std::wstring &ouptut) {
    int pos = 0;
    int size = 0;
    int retval;

    retval = _findPositionByHeader(head, key, pos);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant find position by head" << std::endl;
        return STATUS_FAILURE;
    }

    retval = parser.parseHeadFromStringGetSize(head, size);
    if (retval != STATUS_SUCCESS) {
        return STATUS_FAILURE;
    }

    pos += SIZE_OF_HEADER;
    size -= SIZE_OF_HEADER;

    retval = file.readFromFileByPosition(pos, size, ouptut);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "is not working" << std::endl;
        return retval;
    }

#ifdef WITH_ENCODER
    std::wstring decodedOuptut;
    retval = encoder.decodeStringByKey(ouptut, key, decodedOuptut);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant decode body" << std::endl;
        return STATUS_FAILURE;
    }
    ouptut.clear();
    ouptut.append(decodedOuptut);
#endif

    return retval;
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
        std::wcout << LOG_ERROR << "file is empty" << std::endl;
        return true;
    }
    int retval = file.readFromFileByPosition(pos, SIZE_OF_HEADER, buff);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "isValidKey/readFromFileByPosition: retval = " << retval << std::endl;
        return STATUS_FAILURE;
    }

#ifdef WITH_ENCODER
    std::wstring decudedBuff;
    retval = encoder.decodeStringByKey(buff, key, decudedBuff);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant decode key" << std::endl;
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
            std::wcout << LOG_WARN << "performReadAllDate end of file" << std::endl;
            return STATUS_SUCCESS;
        }
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "performReadAllDate failure" << std::endl;
        }
#ifdef WITH_ENCODER
        std::wstring decodedBuff;
        retval = encoder.decodeStringByKey(buff, key, decodedBuff);
        if (retval != STATUS_SUCCESS) {
            std::wcout << "cant decode buffer when read all date" << std::endl;
            return STATUS_FAILURE;
        }
        buff.clear();
        buff.append(decodedBuff);
#endif
        retval = parser.parseHeadFromString(buff, date, size);
        if (retval != STATUS_SUCCESS) {
            std::wcout << LOG_ERROR << "parser.parseHeadFromString retval = " << retval << std::endl;
            break;
        }
        std::wcout << LOG_DEBUG << "dateList push_back: date = " << date << std::endl;
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
    std::wstring head;
    std::wstring time;
    std::wstring body;
    std::wstring dateString;
    int retval;

    retval = datetime.convertTmDateToString(date, dateString);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant convert tm to string" << std::endl;
        return STATUS_FAILURE;
    }

    retval = _findPositionByDate(dateString, key, pos);
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
    std::wstring decodedHead;
    retval = encoder.decodeStringByKey(head, key, decodedHead);
    if (retval != STATUS_SUCCESS) {
        std::wcout << "cant decode head on read by date" << std::endl;
        return STATUS_FAILURE;
    }
    head.clear();
    head.append(decodedHead);
#endif

    retval = parser.parseHeadFromStringGetTimeString(head, time);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "cant get time from head" << std::endl;
        return STATUS_FAILURE;
    }

    retval = _performReadBodyByHead(head, key, body);
    if (retval != STATUS_SUCCESS) {
        std::wcout << LOG_ERROR << "failure on read body" << std::endl;
        return retval;
    }

    outputBody.clear();
    outputBody.append(time + L'\n' + body + L"\n\n");
    return STATUS_SUCCESS;
}
