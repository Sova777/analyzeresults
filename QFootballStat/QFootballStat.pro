TEMPLATE = app
TARGET = QFootballStat
VERSION = 1.0.0
QT += core gui xml
DEPENDPATH += . src
INCLUDEPATH += . src

HEADERS += src/constants.h \
           src/Filter.h \
           src/MainWindow.h \
           src/Record.h \
           src/Report.h \
           src/XmlFileReader.h
FORMS += src/MainWindow.ui
SOURCES += src/main.cpp \
           src/Filter.cpp \
           src/MainWindow.cpp \
           src/Record.cpp \
           src/Report.cpp \
           src/XmlFileReader.cpp
RESOURCES += src/resources.qrc
