#include "encoding_test.h"
#include "encoder.h"

#include <QDebug>

void test_encode_decode() {
    Encoder encoder;
    char key[5] = "key";
    char src[20] = "somesource123";
    char dest[20] = "0";
    qDebug() << "key: " << key << ", src: " << src << ", dest:" << dest;
    encoder.encodeStringByKey(key, src, dest);

    qDebug() << "key: " << key << ", src: " << src << ", dest:" << dest;
    encoder.decodeStringByKey(key, dest, src);

    qDebug() << "key: " << key << ", src: " << src << ", dest:" << dest;
}
