TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)
DEFINES += STANDALONE
LIBS += $$BornAgainCore_LIB
SOURCES += MesoCrystal1.cpp SampleBuilder.cpp
HEADERS += MesoCrystal1.h SampleBuilder.h


