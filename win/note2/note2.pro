#-------------------------------------------------
#
# Project created by QtCreator 2018-12-08T21:50:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = note2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

# Disable qDebug output
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
    main.cpp \
    encoder.cpp \
    file.cpp \
    interface/mainwindow.cpp \
    interface/treeitem.cpp \
    test/main_test.cpp \
    test/file_test.cpp \
    test/encoding_test.cpp \
    test/interface_test.cpp \
    test/utils_test.cpp \
    note.cpp \
    parser.cpp

HEADERS += \
    encoder.h \
    file.h \
    interface/treeitem.h \
    interface/mainwindow.h \
    test/main_test.h \
    test/file_test.h \
    test/interface_test.h \
    test/encoding_test.h \
    test/utils_test.h \
    note.h \
    parser.h \
    config.h

FORMS += \
        interface/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
