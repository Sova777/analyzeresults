# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Linux/GNU-Linux-x86
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
OBJECTS_DIR = build/Linux/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += ../AnalyzeFootballResults 
LIBS += -Wl,-rpath ../AnalyzeFootballResults/dist/Linux/GNU-Linux-x86 ../AnalyzeFootballResults/dist/Linux/GNU-Linux-x86/libAnalyzeFootballResults.so  
