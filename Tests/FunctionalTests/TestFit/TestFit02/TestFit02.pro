TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)

myIncludes = $$BornAgainCore_INCLUDEPATH $$BornAgainFit_INCLUDEPATH

INCLUDEPATH += $$myIncludes
DEPENDPATH  += $$myIncludes

DEFINES += STANDALONE
LIBS += $$BornAgainCore_LIB $$BornAgainFit_LIB
#isEmpty(ROOT_FRAMEWORK) {
#    LIBS += $$RootMinimizers_LIB
#}

SOURCES += TestFit02.cpp \
    SampleBuilder.cpp
HEADERS += TestFit02.h \
    SampleBuilder.h

