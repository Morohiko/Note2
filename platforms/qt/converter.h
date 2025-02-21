#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <QString>

class Converter {
public:
    static QString toQString(std::wstring &str) {
        return QString::fromStdWString(str);
    }

    static std::wstring toStdWString(QString &str) {
        return str.toStdWString();
    }

    static std::string toStdString(QString &str) {
        return str.toStdString();
    }

    static tm dateToTm(QDate &date) {
        tm tm = {};
        tm.tm_year = date.year();
        tm.tm_mon = date.month();
        tm.tm_mday = date.day();
        return tm;
    }

    static tm dateTimeToTm(QDateTime &datetime) {
        tm tm = {};
        tm.tm_year = datetime.date().year();
        tm.tm_mon = datetime.date().month();
        tm.tm_mday = datetime.date().day();
        tm.tm_hour = datetime.time().hour();
        tm.tm_min = datetime.time().minute();    
        tm.tm_sec = datetime.time().second();
        return tm;
    }
};

#endif // CONVERTER_H
