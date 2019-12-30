#include "encoder.h"

#include <QDebug>

QString Encoder::encodeString(QString *src) {
    Q_ASSERT(src);

    QString dest;

    for (int i = 0; i < src->length(); i++) {
        dest.append(src->at(i).toUpper());
    }
    return dest;
}

QString Encoder::decodeString(QString *src) {
    Q_ASSERT(src);

    QString dest;

    for (int i = 0; i < src->length(); i++) {
        dest.append(src->at(i).toLower());
    }
    return dest;
}

QString Encoder::encodeStringByKey(QString *src, QString *key) {
    Q_ASSERT(src);

    QString dest;
    int nkey = 0;

    for (int i = 0; i < src->size(); i++) {
        ushort buff = src->at(i).unicode() + static_cast<ushort>(key->at(nkey).unicode());
        dest.append(QChar(buff));
        if (key->size() <= ++nkey) nkey = 0;
    }
    qDebug() << "DEBUG: encodeStringByKey src = " << *src << ", dest = " << dest;
    return dest;
}


QString Encoder::decodeStringByKey(QString *src, QString *key) {
    Q_ASSERT(src);

    QString dest;

    int nkey = 0;
    for (int i = 0; i < src->size(); i++) {
        ushort buff = src->at(i).unicode() - static_cast<ushort>(key->at(nkey).unicode());
        dest.append(QChar(buff));
        if (key->size() <= ++nkey) nkey = 0;
    }
    qDebug() << "DEBUG: decodeStringByKey src = " << *src << ", dest = " << dest;
    return dest;
}

int Encoder::encodeString(char *src, char *dest) {
    Q_ASSERT(src); Q_ASSERT(dest);

    qDebug() << "src = " << src << ", dest = " << dest;
	return 0;
}

int Encoder::decodeString(char *src, char *dest) {
    Q_ASSERT(src); Q_ASSERT(dest);

    qDebug() << "src = " << src << ", dest = " << dest;
    return 0;
}

int Encoder::encodeStringByKey(char *key, char *src, char *dest) {
    Q_ASSERT(src); Q_ASSERT(dest); Q_ASSERT(key);

    char *iter_src = src;
	char *iter_dest = dest;
	char *iter_key = key;
	int i = 0;
	
	while (*iter_src) {
        *iter_dest = (unsigned char)*iter_src + (unsigned char)*iter_key;
		//sprintf(*iter_dest, "%c", (*iter_src + *iter_key));
        qDebug() << *iter_dest;
		*iter_dest = (unsigned char)*iter_src - (unsigned char)*iter_key;
		//sprintf(*iter_dest, "%c", (*iter_src - *iter_key));

        qDebug() << *iter_dest;

		iter_dest++; iter_src++; iter_key++;
		if (!*iter_dest) {
			iter_key = &key[0];
		}
		i++;
	}
	return 0;
}

int Encoder::decodeStringByKey(char *key, char *src, char *dest) {
    Q_ASSERT(src); Q_ASSERT(dest); Q_ASSERT(key);

	char *iter_src = &src[0];
	char *iter_dest = &dest[0];
	char *iter_key = &key[0];

	while (*iter_src) {
		*iter_dest = *iter_src - *iter_key;
		iter_dest++; iter_src++; iter_key++;
		if (!*iter_dest) {
			iter_key = &key[0];
		}
	}
	return 0;
}
