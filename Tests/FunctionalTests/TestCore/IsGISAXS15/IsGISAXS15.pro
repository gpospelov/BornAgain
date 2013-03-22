TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)
DEFINES += STANDALONE
LIBS += $$PWD/../../../../lib/libBornAgainCore.so

SOURCES += IsGISAXS15.cpp
HEADERS += IsGISAXS15.h

