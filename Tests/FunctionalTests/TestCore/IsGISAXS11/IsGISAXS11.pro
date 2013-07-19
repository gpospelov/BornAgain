TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)
DEFINES += STANDALONE
LIBS += $$BornAgainCore_LIB
SOURCES += IsGISAXS11.cpp
HEADERS += IsGISAXS11.h
