TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)
DEFINES += STANDALONE
LIBS += $$PWD/../../../../lib/libBornAgainCore.so

SOURCES += IsGISAXS01.cpp
HEADERS += IsGISAXS01.h

