#include "file.h"
#include "config.h"

#include <QTextStream>
#include <QDebug>

int File::cFileExists(const QString filename) {
    qDebug() << "DEBUG: filename = " << filename;
    QFile file(filename);

    if (!file.exists()) {
        qDebug()  << "ERROR: qWriteToEndFile pathStirng = " << path;
        return -1;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }

    file.close();
	return 0;
}

int File::setPathToFile(QString src) {
    if (cFileExists(src)) {
        qDebug() << "ERROR: file with path not exist" << src;
        return -1;
    }
    path = src;
    return 0;
}

int File::qWriteToEndFile(QString src) {
    if (path.size() < 1) {
        qDebug()  << "ERROR: qWriteToEndFile path == nullptr";
        return -1;
    }

    QFile file(path);
    if (!file.exists()) {
        qDebug()  << "ERROR: qWriteToEndFile pathStirng = " << path;
        return -1;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug()  << "ERROR: qWriteToEndFile pathStirng = " << path;
        return -1;
    }

    QTextStream out(&file);
    out.setCodec(CODEC);

    out << src;
    file.close();
    return 0;
}

QString File::qReadFromFile() {
    if (cFileExists(path)) {
        qDebug() << "ERROR: file not exist";
        return nullptr;
    }
    QFile file(path);

    if (!file.exists()) {
        qDebug()  << "ERROR: qWriteToEndFile pathStirng = " << path;
        return nullptr;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }
    QString line;
    while (!file.atEnd()) {
        line += file.readLine();
        qDebug() << "DEBUG: line = " << line.data();
    }
    file.close();

    return line;
}

QString File::qReadFromFileByPosition(int pos, int size) {
    if (cFileExists(path)) {
        qDebug() << "ERROR: file not exist";
        return nullptr;
    }
    QFile file(path);

    if (!file.exists()) {
        qDebug()  << "ERROR: qWriteToEndFile pathStirng = " << path;
        return nullptr;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    QTextStream in(&file);
    in.setCodec(CODEC);
#ifdef UNICODE
    pos *= 2; pos += 2;
#endif
    if (in.seek(pos + size) == false) {
        qDebug()  << "ERROR: its end of file pos + size = " << pos + size;
        return nullptr;
    }

    in.seek(pos);
    QString line = in.readLine(size);

    qDebug() << "qReadFromFileByPosition pos = " << pos << "line == " << line;

    file.close();
    return line;
}
