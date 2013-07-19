TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)

myIncludes = $$BornAgainCore_INCLUDEPATH $$BornAgainFit_INCLUDEPATH

INCLUDEPATH += $$myIncludes
DEPENDPATH  += $$myIncludes

DEFINES += STANDALONE
LIBS += $$BornAgainCore_LIB $$BornAgainFit_LIB $$RootMathMore_LIB
isEmpty(ROOT_FRAMEWORK) {
    LIBS += $$RootMinimizers_LIB
}

SOURCES += TestFit01.cpp
HEADERS += TestFit01.h

