#-------------------------------------------------
#
# Project created by QtCreator 2014-04-20T17:22:55
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SKproject_0420
TEMPLATE = app

CONFIG  += qaxcontainer

SOURCES += main.cpp\
    UI/UI_MainWindow.cpp \
    DB/DB_CONNECT.cpp \
    UI/UI_SELECT_TABLE.cpp \
    INTERFACE/ItemDelegate.cpp \
    INTERFACE/EXPORT.cpp \
    UI/UI_EXPORT.cpp \
    UI/UI_IMPORT.cpp \
    INTERFACE/IMPORT.cpp \
    LOGIC/LOGIC_TABLE.cpp \
    UI/UI_IMPORT_DETAIL.cpp \
    UI/UI_IMPORT_PREVIEW.cpp

HEADERS  += UI/UI_MainWindow.h \
    DB/DB_CONNECT.h \
    UI/UI_SELECT_TABLE.h \
    INTERFACE/ItemDelegate.h \
    INTERFACE/EXPORT.h \
    UI/UI_EXPORT.h \
    UI/UI_IMPORT.h \
    INTERFACE/IMPORT.h \
    LOGIC/LOGIC_TABLE.h \
    UI/UI_IMPORT_DETAIL.h \
    UI/UI_IMPORT_PREVIEW.h


FORMS    += UI/UI_MainWindow.ui \
    UI/UI_SELECT_TABLE.ui \
    UI/UI_EXPORT.ui \
    UI/UI_IMPORT.ui \
    UI/UI_IMPORT_DETAIL.ui \
    UI/UI_IMPORT_PREVIEW.ui

RESOURCES += \
    RES/RES.qrc
