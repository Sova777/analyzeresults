# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Windows/MinGW-Windows
TARGET = QAnalyzeFootballResults
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += mainform.cpp main.cpp
HEADERS += mainform.h
FORMS += mainform.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Windows/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc.exe
QMAKE_CXX = g++.exe
DEFINES += 
INCLUDEPATH += ../AnalyzeFootballResults 
LIBS += -L../AnalyzeFootballResults/dist/Windows/MinGW-Windows ../AnalyzeFootballResults/dist/Windows/MinGW-Windows/libAnalyzeFootballResults.dll  
