# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Windows/MinGW-Windows
TARGET = QFootballStat
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core gui
SOURCES += MainWindow.cpp main.cpp
HEADERS += MainWindow.h
FORMS += MainWindow.ui
RESOURCES += resources.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Windows/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += ../AnalyzeFootballResults 
LIBS += -L../AnalyzeFootballResults/dist/Windows/MinGW-Windows ../AnalyzeFootballResults/dist/Windows/MinGW-Windows/libAnalyzeFootballResults.dll  
