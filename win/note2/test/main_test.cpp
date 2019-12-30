#include "main_test.h"
#include "encoding_test.h"
#include "file_test.h"
#include "interface_test.h"
#include "utils_test.h"

#include <QDebug>

void simple_test() {
    char c = 'a';
    char *p = &c;
    *p = *p + 1;
    qDebug() << *p;
}

int run_test() {
    return 0;
}

