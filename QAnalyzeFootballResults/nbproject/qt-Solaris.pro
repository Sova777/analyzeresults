# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Solaris/OracleSolarisStudio-Solaris-x86
TARGET = QAnalyzeFootballResults
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui
SOURCES += main.cpp mainform.cpp
HEADERS += mainform.h
FORMS += mainform.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Solaris/OracleSolarisStudio-Solaris-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = cc
QMAKE_CXX = CC
DEFINES += 
INCLUDEPATH += ../AnalyzeFootballResults 
LIBS += -R../AnalyzeFootballResults/dist/Unix/OracleSolarisStudio-Solaris-x86 ../AnalyzeFootballResults/dist/Unix/OracleSolarisStudio-Solaris-x86/libAnalyzeFootballResults.so  
