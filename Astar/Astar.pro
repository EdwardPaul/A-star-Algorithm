QT += core
QT -= gui

TARGET = Astar
CONFIG += console
CONFIG -= app_bundle
CONFIG += C++11
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES += main.cpp \
    astar.cpp \
    map.cpp

HEADERS += \
    astar.h \
    map.h \
    struct.h \
    heuristics.h \
    configuration.h \
    const.h

