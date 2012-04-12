QT -= gui
QT -= core

TARGET = gtest
TEMPLATE = lib
CONFIG += staticlib

mygtest = gtest-1.6.0

INCLUDEPATH += ./$$mygtest/include ./$$mygtest

SOURCES += \
    ./$$mygtest/src/gtest.cc \
    ./$$mygtest/src/gtest-typed-test.cc \
    ./$$mygtest/src/gtest-test-part.cc \
    ./$$mygtest/src/gtest-printers.cc \
    ./$$mygtest/src/gtest-port.cc \
    ./$$mygtest/src/gtest-filepath.cc \
    ./$$mygtest/src/gtest-death-test.cc \
    ./$$mygtest/src/gtest-all.cc \
    ./$$mygtest/src/gtest_main.cc

HEADERS += \
    ./$$mygtest/src/gtest-internal-inl.h

OBJECTS_DIR = obj

#target.path = ../../lib
#INSTALLS += target
#QMAKE_CLEAN += $(TARGET) $$target.path/$(TARGET)
QMAKE_CLEAN = $(TARGET)


