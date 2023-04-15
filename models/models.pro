TARGET = model
TEMPLATE = lib
CONFIG += shared x86_64
QT += sql qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers
DEPENDPATH  += ../helpers
LIBS += -L../lib -lhelper
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)
HEADERS += sqlobjects/bookobject.h
HEADERS += objects/book.h
SOURCES += objects/book.cpp
HEADERS += \
    book_service.h
SOURCES += \
    book_service.cpp
