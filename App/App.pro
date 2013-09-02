TEMPLATE = app
CONFIG  += console
CONFIG  -= qt
CONFIG  -= app_bundle
QT      -= core gui


# -----------------------------------------------------------------------------
# generate ROOT dictionaries
# -----------------------------------------------------------------------------
BORNAGAIN_ROOT_DICT_FOR_CLASSES =  inc/App.h inc/AppLinkDef.h
BORNAGAIN_ROOT_DICT_INCLUDES = $$PWD/../Core/Tools/inc
include($$PWD/../shared.pri)

isEmpty(ROOT_FRAMEWORK) {
    error("ROOT is absent")
}

# -----------------------------------------------------------------------------
# propagating operation system type inside the code
# -----------------------------------------------------------------------------
# (note, that when Qt libraries are used, it is already done in <qglobal.h>)
macx {
    DEFINES += Q_OS_MAC
}
unix:!macx {
    DEFINES += Q_OS_LINUX
}

FUNCTIONAL_TESTS = $$PWD/../Tests/FunctionalTests/TestCore

# -----------------------------------------------------------------------------
# Our source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    $${FUNCTIONAL_TESTS}/IsGISAXS06/IsGISAXS06.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS07/IsGISAXS07.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS08/IsGISAXS08.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS10/IsGISAXS10.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS11/IsGISAXS11.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS15/IsGISAXS15.cpp \
    src/AppOptionsDescription.cpp \
    src/DrawHelper.cpp \
    src/FitSuiteDrawObserver.cpp \
    src/FitSuiteWriteTreeObserver.cpp \
    src/FunctionalTestFactory.cpp \
    src/IFunctionalTest.cpp \
    src/IsGISAXSData.cpp \
    src/IsGISAXSTools.cpp \
    src/SampleFactory.cpp \
    src/StandardSamples.cpp \
    src/TestConvolution.cpp \
    src/TestDetectorResolution.cpp \
    src/TestDiffuseReflection.cpp \
    src/TestFittingBenchmark.cpp \
    src/TestFittingModule1.cpp \
    src/TestFittingModule2.cpp \
    src/TestFittingModule3.cpp \
    src/TestFormFactor.cpp \
    src/TestFormFactors.cpp \
    src/TestFourier.cpp \
    src/TestFumiliLMA.cpp \
    src/TestIsGISAXS1.cpp \
    src/TestIsGISAXS10.cpp \
    src/TestIsGISAXS11.cpp \
    src/TestIsGISAXS12.cpp \
    src/TestIsGISAXS13.cpp \
    src/TestIsGISAXS14.cpp \
    src/TestIsGISAXS15.cpp \
    src/TestIsGISAXS2.cpp \
    src/TestIsGISAXS3.cpp \
    src/TestIsGISAXS4.cpp \
    src/TestIsGISAXS5.cpp \
    src/TestIsGISAXS6.cpp \
    src/TestIsGISAXS7.cpp \
    src/TestIsGISAXS8.cpp \
    src/TestIsGISAXS9.cpp \
    src/TestMesoCrystal1.cpp \
    src/TestMesoCrystal2.cpp \
    src/TestMiscellaneous.cpp \
    src/TestMultiLayerRoughness.cpp \
    src/TestPerformance.cpp \
    src/TestPolarizedDWBA.cpp \
    src/TestRootTree.cpp \
    src/TestRoughness.cpp \
    src/TestSpecularMagnetic.cpp \
    src/TestSpecularMatrix.cpp \
    src/TestToySimulation.cpp \
    src/TreeEventStructure.cpp \
    src/main.cpp \
    src/TestBugs.cpp


HEADERS += \
    $${FUNCTIONAL_TESTS}/IsGISAXS06/IsGISAXS06.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS07/IsGISAXS07.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS08/IsGISAXS08.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS10/IsGISAXS10.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS11/IsGISAXS11.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS15/IsGISAXS15.h \
    inc/App.h \
    inc/AppLinkDef.h \
    inc/AppOptionsDescription.h \
    inc/DrawHelper.h \
    inc/FitSuiteDrawObserver.h \
    inc/FitSuiteObserverFactory.h \
    inc/FitSuiteWriteTreeObserver.h \
    inc/FunctionalTestFactory.h \
    inc/IFunctionalTest.h \
    inc/IsGISAXSData.h \
    inc/IsGISAXSTools.h \
    inc/SampleFactory.h \
    inc/StandardSamples.h \
    inc/TestConvolution.h \
    inc/TestDetectorResolution.h \
    inc/TestDiffuseReflection.h \
    inc/TestFittingBenchmark.h \
    inc/TestFittingModule1.h \
    inc/TestFittingModule2.h \
    inc/TestFittingModule3.h \
    inc/TestFormFactor.h \
    inc/TestFormFactors.h \
    inc/TestFourier.h \
    inc/TestFumiliLMA.h \
    inc/TestIsGISAXS1.h \
    inc/TestIsGISAXS10.h \
    inc/TestIsGISAXS11.h \
    inc/TestIsGISAXS12.h \
    inc/TestIsGISAXS13.h \
    inc/TestIsGISAXS14.h \
    inc/TestIsGISAXS15.h \
    inc/TestIsGISAXS2.h \
    inc/TestIsGISAXS3.h \
    inc/TestIsGISAXS4.h \
    inc/TestIsGISAXS5.h \
    inc/TestIsGISAXS6.h \
    inc/TestIsGISAXS7.h \
    inc/TestIsGISAXS8.h \
    inc/TestIsGISAXS9.h \
    inc/TestMesoCrystal1.h \
    inc/TestMesoCrystal2.h \
    inc/TestMiscellaneous.h \
    inc/TestMultiLayerRoughness.h \
    inc/TestPerformance.h \
    inc/TestPolarizedDWBA.h \
    inc/TestRootTree.h \
    inc/TestRoughness.h \
    inc/TestSpecularMagnetic.h \
    inc/TestSpecularMatrix.h \
    inc/TestToySimulation.h \
    inc/TreeEventStructure.h \
    inc/TestBugs.h

myIncludes = $$PWD/inc \
             $${FUNCTIONAL_TESTS}/IsGISAXS06 \
             $${FUNCTIONAL_TESTS}/IsGISAXS07 \
             $${FUNCTIONAL_TESTS}/IsGISAXS08 \
             $${FUNCTIONAL_TESTS}/IsGISAXS10 \
             $${FUNCTIONAL_TESTS}/IsGISAXS11 \
             $${FUNCTIONAL_TESTS}/IsGISAXS15

myIncludes += $${BornAgainCore_INCLUDEPATH} $${BornAgainFit_INCLUDEPATH} $${ROOT_FRAMEWORK_INCLUDEPATH}

INCLUDEPATH += $$myIncludes
DEPENDPATH  += $$myIncludes

LIBS += $$BornAgainCore_LIB $$BornAgainFit_LIB $$RootMathMore_LIB
LIBS += $${ROOT_FRAMEWORK_LIBS}


