TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    ../../Core/src/OutputData.cpp

INCLUDEPATH += ../../ThirdParty/gtest-1.6.0/include ../../Core/inc

LIBS += -L../../ThirdParty/Qt_gtest -lgtest

HEADERS += \
    NamedVectorTest.h \
    OutputDataTest.h
