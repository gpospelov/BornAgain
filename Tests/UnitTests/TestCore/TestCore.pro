# -----------------------------------------------------------------------------
# qmake project file to compile and run unit test of libBornAgainCore
# -----------------------------------------------------------------------------
TEMPLATE = app
CONFIG  -= qt app_bundle
CONFIG  += console release
TARGET = TestCore
DESTDIR = $$PWD
QT      -= core gui

# including common project properties
include(../../../shared.pri)

SOURCES += main.cpp

HEADERS += \
    AxisDoubleTest.h \
    BeamTest.h \
    ChiSquaredModuleTest.h \
    CVectorTest.h \
    DetectorTest.h \
    InstrumentTest.h \
    IParameterizedTest.h \
    KVectorTest.h \
    MaskTest.h \
    OutputDataTest.h \
    OutputDataIteratorTest.h \
    ParameterPoolTest.h \
    RealParameterWrapperTest.h \
    SimulationTest.h \
    ThreadInfoTest.h \
    LayerTest.h \
    ParticleTest.h

# -----------------------------------------------------------------------------
# dependencies
# -----------------------------------------------------------------------------
DEPENDPATH  += $$BornAgainCore_INCLUDE_DIR
INCLUDEPATH *= $$EIGEN_INCLUDE_DIR
INCLUDEPATH *= $$BOOST_INCLUDE_DIR
INCLUDEPATH += $$BornAgainCore_INCLUDE_DIR $$gtest_INCLUDE_DIR
LIBS += $$BOOST_LIBRARY $$BornAgainCore_LIBRARY $$gtest_LIBRARY

# -----------------------------------------------------------------------------
# runs automatically tests right after linking
# -----------------------------------------------------------------------------
QMAKE_POST_LINK += $$PWD/$(TARGET)

