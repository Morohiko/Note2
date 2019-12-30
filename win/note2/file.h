#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include <QFile>

class File
{
public:
    int qWriteToEndFile(QString src);
    QString qReadFromFile();
    QString qReadFromFileByPosition(int pos, int size);
    int setPathToFile(QString src);
private:
    QString path;
    int cFileExists(const QString filename);
};


