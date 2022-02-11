#include <QApplication>

#include "note.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Note note;
    note.start();

    return a.exec();
}
