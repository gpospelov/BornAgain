QT       -= core
QT       -= gui

TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG -= app_bundle

SOURCES += main.cpp \
    $$PWD/../../Core/src/OutputData.cpp \
    $$PWD/../../Core/src/Exceptions.cpp

INCLUDEPATH += $$PWD/../../ThirdParty/gtest/include ../../Core/inc

LIBS += -L$$PWD/../../ThirdParty/gtest -lgtest

HEADERS += \
    NamedVectorTest.h \
    OutputDataTest.h

OBJECTS_DIR = obj

# the projects depends from third party library "google test"
PRE_TARGETDEPS += $$PWD/../../ThirdParty/gtest/libgtest.a
makelibs.target = $$PWD/../../ThirdParty/gtest/libgtest.a
#makelibs.target = $$PWD/../../ThirdParty/gtest/libgtest.a
makelibs.commands = (cd $$PWD/../../ThirdParty/gtest; qmake; make)
makelibs.depends = FORCE
QMAKE_EXTRA_TARGETS += makelibs

# runs automatically tests right after linking
QMAKE_POST_LINK = ./$(TARGET)
