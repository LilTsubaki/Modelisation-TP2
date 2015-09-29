QT += core
QT += gui

TARGET = tp02_modelisation
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES += main.cpp \
    maillage.cpp

HEADERS += \
    maillage.h

