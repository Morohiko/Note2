#include <QApplication>

#include "note.h"

#include "test/main_test.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Note note;
    note.start();

    return a.exec();
}
