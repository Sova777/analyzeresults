# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Unix/MinGW-Windows
TARGET = QAnalyzeFootballResults
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core gui
SOURCES += mainform.cpp main.cpp
HEADERS += mainform.h
FORMS += mainform.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Unix/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc.exe
QMAKE_CXX = g++.exe
DEFINES += 
INCLUDEPATH += ../AnalyzeFootballResults 
LIBS += -L../AnalyzeFootballResults/dist/Unix/MinGW-Windows ../AnalyzeFootballResults/dist/Unix/MinGW-Windows/libAnalyzeFootballResults.so  
