#include "utils_test.h"
#include "utils.h"
#include "string.h"

#include <QDebug>

void test_get_date_time() {
    char buff[100];

    //get_string_date_time(&buff[0]);
    qDebug() << "strlen = " << strlen(buff) << "buff = " << buff;
}

