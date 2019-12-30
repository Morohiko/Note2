#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <QString>

class Encoder
{
public:
    QString encodeString(QString *src);
    QString decodeString(QString *src);

    QString encodeStringByKey(QString *src, QString *key);
    QString decodeStringByKey(QString *src, QString *key);

    // not recomended, unicode issue
    int encodeString(char *src, char *dest);
    int decodeString(char *src, char *dest);

    int encodeStringByKey(char *key, char *src, char *dest);
    int decodeStringByKey(char *key, char *src, char *dest);
};

