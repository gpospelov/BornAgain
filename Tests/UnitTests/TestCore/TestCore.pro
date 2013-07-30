###############################################################################
# qmake project file to compile and run unit test of ScattCore library
###############################################################################
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

#OBJECTS_DIR = obj

INCLUDEPATH += $${PWD}/../../../ThirdParty/gtest/gtest-1.6.0/include
DEPENDPATH += ./

###############################################################################
# generating package dependency flags
###############################################################################
MY_DEPENDENCY_LIB = gtest BornAgainCore
MY_DEPENDENCY_DEST =$$PWD/../../..
# INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
#    INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc/$${dep}
}

###############################################################################
# runs automatically tests right after linking
###############################################################################
QMAKE_POST_LINK = $$PWD/$(TARGET)
