#include <QApplication>

#include "note.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Note note;

    MainWindow window;
    window.setCallbacks(Note::setFilenameHandler, Note::performReadByDateHandler,
                        Note::performReadAllDateHandler, Note::performWriteToFileHandler);
    window.show();
    // window.setCallbacks()
    // note.start();

    return a.exec();
}
