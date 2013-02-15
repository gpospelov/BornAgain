###############################################################################
# qmake project file to compile and run unit test of ScattCore library
###############################################################################
TEMPLATE = app
CONFIG  -= qt app_bundle
CONFIG  += console build_all
QT      -= core gui

# including common project properties
include($$PWD/../../../shared.pri)

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

OBJECTS_DIR = obj

#CORE = $$PWD/../../../Core
#CORE_HEADERS = $${CORE}/Algorithms/inc $${CORE}/FormFactors/inc $${CORE}/Geometry/inc $${CORE}/Samples/inc $${CORE}/Tools/inc $${CORE}/../ThirdParty/gtest/gtest-1.6.0/include
#INCLUDEPATH += $${CORE_HEADERS}
#DEPENDPATH += $${CORE_HEADERS} $PWD

INCLUDEPATH += $${PWD}/../../../ThirdParty/gtest/gtest-1.6.0/include

###############################################################################
# generating package dependency flags
###############################################################################
MY_DEPENDENCY_LIB = gtest BornAgainCore
MY_DEPENDENCY_DEST =$$PWD/../../..
SONAME = so
# INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
#    INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc/$${dep}
}

###############################################################################
# runs automatically tests right after linking
###############################################################################
QMAKE_POST_LINK = $$PWD/$(TARGET) 2> /dev/null
