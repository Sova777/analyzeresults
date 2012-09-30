TEMPLATE = app
TARGET = qfootballstat
VERSION = 1.0.0
QT += core gui xml
#QMAKE_CXXFLAGS = -Wno-unused-parameter
#CONFIG += console
DEPENDPATH += . src
INCLUDEPATH += . src

HEADERS += src/constants.h \
           src/ContextMenu.h \
           src/EditReport.h \
           src/Filter.h \
           src/Find.h \
           src/MainWindow.h \
           src/Record.h \
           src/Report.h \
           src/XmlFileReader.h \
           src/XmlFilter.h
FORMS += src/MainWindow.ui \
         src/EditReport.ui \
         src/Find.ui
SOURCES += src/main.cpp \
           src/ContextMenu.cpp \
           src/EditReport.cpp \
           src/Filter.cpp \
           src/Find.cpp \
           src/MainWindow.cpp \
           src/Record.cpp \
           src/Report.cpp \
           src/XmlFileReader.cpp \
           src/XmlFilter.cpp
RESOURCES += src/resources.qrc
RC_FILE += src/QFootballStat.rc
