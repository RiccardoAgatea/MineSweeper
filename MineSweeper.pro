QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineSweeper
TEMPLATE = app

MOC_DIR = mocfiles
OBJECTS_DIR = objfiles
RCC_DIR = rccfiles

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
	cellwidget.cpp \
	main.cpp \
	minesweeper.cpp \
	view.cpp

HEADERS += \
    cellwidget.h \
    minesweeper.h \
    view.h

RESOURCES += \
	media.qrc
