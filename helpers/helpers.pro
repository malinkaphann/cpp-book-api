TARGET = helper
TEMPLATE = lib
CONFIG += shared x86_64
QT += xml qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH +=
DEPENDPATH  +=
LIBS +=
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)

HEADERS += applicationhelper.h
SOURCES += applicationhelper.cpp
HEADERS += status.h
HEADERS += \
    not_found_exception.h
HEADERS += \
    validation_exception.h
HEADERS += \
    api_exception.h
SOURCES +=
HEADERS += \
    book_validator.h
SOURCES += \
    book_validator.cpp
HEADERS +=
SOURCES +=
HEADERS += \
    nothing_updated_exception.h
SOURCES +=
HEADERS += \
    database_exception.h
SOURCES +=
