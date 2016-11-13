#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T23:20:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_for_pdp11
TEMPLATE = app

QT += sql

SOURCES += main.cpp\
        widget.cpp \
    bitmapwidget.cpp \
    tablemodel.cpp \
    process.cpp \
    styleddelegate.cpp

HEADERS  += widget.h \
    formain.h \
    bitmapwidget.h \
    tablemodel.h \
    process.h \
    styleddelegate.h

FORMS    += widget.ui
