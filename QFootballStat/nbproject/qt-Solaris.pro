# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Solaris/OracleSolarisStudio-Linux-x86
TARGET = QFootballStat
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core gui xml
SOURCES += MainWindow.cpp main.cpp Record.cpp XmlFileReader.cpp
HEADERS += Record.h XmlFileReader.h constants.h MainWindow.h
FORMS += MainWindow.ui
RESOURCES += resources.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Solaris/OracleSolarisStudio-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = cc
QMAKE_CXX = CC
DEFINES += 
INCLUDEPATH += ../AnalyzeFootballResults 
LIBS += 
QMAKE_LFLAGS=-library=stlport4
QMAKE_CXXFLAGS=-library=stlport4
