QT -= GUI
TARGET = gtest
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../gtest-1.6.0 ../gtest-1.6.0/include

SOURCES += \
    ../gtest-1.6.0/src/gtest.cc \
    ../gtest-1.6.0/src/gtest-typed-test.cc \
    ../gtest-1.6.0/src/gtest-test-part.cc \
    ../gtest-1.6.0/src/gtest-printers.cc \
    ../gtest-1.6.0/src/gtest-port.cc \
    ../gtest-1.6.0/src/gtest-filepath.cc \
    ../gtest-1.6.0/src/gtest-death-test.cc \
    ../gtest-1.6.0/src/gtest-all.cc \
    ../gtest-1.6.0/src/gtest_main.cc

HEADERS += \
    ../gtest-1.6.0/src/gtest-internal-inl.h
