QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adb-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adb.cpp

HEADERS  += mainwindow.h \
    adb.h

FORMS    += mainwindow.ui
