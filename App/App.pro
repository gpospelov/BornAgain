TEMPLATE = app
CONFIG  += console
CONFIG  -= qt
CONFIG  -= app_bundle
QT      -= core gui

include($$PWD/../shared.pri)

FUNCTIONAL_TESTS = $$PWD/../Tests/FunctionalTests/TestCore

# -----------------------------------------------------------------------------
# Our source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    src/AppOptionsDescription.cpp \
    src/CommandLine.cpp \
    src/DrawHelper.cpp \
    src/FunctionalTestFactory.cpp \
    src/IFunctionalTest.cpp \
    src/IsGISAXSData.cpp \
    src/IsGISAXSTools.cpp \
    src/main.cpp \
    src/ROOTMinimizer.cpp \
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
    src/TestFourier.cpp \
    src/TestFresnelCoeff.cpp \
    src/TestFumiliLMA.cpp \
    src/TestIsGISAXS1.cpp \
    src/TestIsGISAXS2.cpp \
    src/TestIsGISAXS3.cpp \
    src/TestIsGISAXS4.cpp \
    src/TestIsGISAXS5.cpp \
    src/TestIsGISAXS7.cpp \
    src/TestIsGISAXS8.cpp \
    src/TestIsGISAXS9.cpp \
    src/TestIsGISAXS10.cpp \
    src/TestIsGISAXS11.cpp \
    src/TestIsGISAXS12.cpp \
    src/TestIsGISAXS13.cpp \
    src/TestMesoCrystal1.cpp \
    src/TestMesoCrystal2.cpp \
    src/TestMiscellaneous.cpp \
    src/TestMultiLayerRoughness.cpp \
    src/TestPerformance.cpp \
    src/TestRootTree.cpp \
    src/TestRoughness.cpp \
    src/TestToyExperiment.cpp \
    src/TreeEventStructure.cpp \
    src/ROOTGSLNLSMinimizer.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS01/IsGISAXS01.cpp \
    src/ROOTGSLSimAnMinimizer.cpp \
    src/FitSuiteObserverFactory.cpp \
    src/MinimizerFactory.cpp

HEADERS += \
    inc/App.h \
    inc/AppLinkDef.h \
    inc/AppOptionsDescription.h \
    inc/CommandLine.h \
    inc/DrawHelper.h \
    inc/FunctionalTestFactory.h \
    inc/IFunctionalTest.h \
    inc/IsGISAXSData.h \
    inc/IsGISAXSTools.h \
    inc/ROOTMinimizer.h \
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
    inc/TestFourier.h \
    inc/TestFresnelCoeff.h \
    inc/TestFumiliLMA.h \
    inc/TestIsGISAXS1.h \
    inc/TestIsGISAXS2.h \
    inc/TestIsGISAXS3.h \
    inc/TestIsGISAXS4.h \
    inc/TestIsGISAXS5.h \
    inc/TestIsGISAXS7.h \
    inc/TestIsGISAXS8.h \
    inc/TestIsGISAXS9.h \
    inc/TestIsGISAXS10.h \
    inc/TestIsGISAXS11.h \
    inc/TestIsGISAXS12.h \
    inc/TestIsGISAXS13.h \
    inc/TestMesoCrystal1.h \
    inc/TestMesoCrystal2.h \
    inc/TestMiscellaneous.h \
    inc/TestMultiLayerRoughness.h \
    inc/TestPerformance.h \
    inc/TestRootTree.h \
    inc/TestRoughness.h \
    inc/TestToyExperiment.h \
    inc/TreeEventStructure.h \
    inc/ROOTMinimizerFunction.h \
    inc/ROOTGSLNLSMinimizer.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS01/IsGISAXS01.h \
    inc/ROOTGSLSimAnMinimizer.h \
    inc/FitSuiteObserverFactory.h \
    inc/MinimizerFactory.h

# additional locations
LOCATIONS = ./inc $${FUNCTIONAL_TESTS}/IsGISAXS01
INCLUDEPATH += $${LOCATIONS}
DEPENDPATH  += $${LOCATIONS}

OBJECTS_DIR = obj

# -----------------------------------------------------------------------------
# generating package dependency flags
# -----------------------------------------------------------------------------
MY_DEPENDENCY_LIB = ScattCore
MY_DEPENDENCY_DEST =$$PWD/..
SONAME = so
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
}

# -----------------------------------------------------------------------------
# adding ROOT libraries
# -----------------------------------------------------------------------------
MYROOT = $$(ROOTSYS)
isEmpty(MYROOT) {
  message("Warning, ROOTSYS environment variable doesn't exist, trying to guess location")
  ROOT_CONFIG_FILE = root-config
  ROOT_CONFIG_FILE_LOCATIONS = /opt/local /usr/local /usr
  for(dir, ROOT_CONFIG_FILE_LOCATIONS): isEmpty(MYROOT): exists($${dir}/bin/$${ROOT_CONFIG_FILE}): MYROOT = $${dir}
  isEmpty(MYROOT): error("Can't find" $${ROOT_CONFIG_FILE} "in" $${ROOT_CONFIG_FILE_LOCATIONS})
  message("Probable ROOTSYS is" $${MYROOT})
}
!isEmpty(MYROOT) {
  !exists($${MYROOT}/bin/root-config): error("No config file "$${MYROOT}/bin/root-config)
  INCLUDEPATH += $$system($${MYROOT}/bin/root-config --incdir)
  LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lMathMore -lMinuit2 -lGeom -lEve -lRGL -lThread -lpthread -lm -ldl
  MYROOTCINT = $${MYROOT}/bin/rootcint
}

# -----------------------------------------------------------------------------
# Hand made addition to generate root dictionaries in the
# absence of rootcint.pri file
# -----------------------------------------------------------------------------
CREATE_ROOT_DICT_FOR_CLASSES = inc/App.h inc/AppLinkDef.h

DICTDEFINES += -DQT_VERSION=0x30000
QT_VERSION=$$[QT_VERSION]
contains( QT_VERSION, "^4.*" ) {
  DICTDEFINES -= -DQT_VERSION=0x30000
  DICTDEFINES *= -DQT_VERSION=0x40000
}
ROOT_CINT_TARGET = $${TARGET}
SOURCES         *= src/$${ROOT_CINT_TARGET}Dict.cpp
rootcint.target       = src/$${ROOT_CINT_TARGET}Dict.cpp
rootcint.commands    += $$MYROOTCINT
rootcint.commands    +=  -f $$rootcint.target  -c -I../Core/Tools/inc $$CREATE_ROOT_DICT_FOR_CLASSES
#rootcint.commands    +=  -f $$rootcint.target  -c -p $$DICTDEFINES $(INCPATH) $$CREATE_ROOT_DICT_FOR_CLASSES
rootcint.depends      = $$CREATE_ROOT_DICT_FOR_CLASSES

rootcintecho.commands = @echo "Generating dictionary $$rootcint.target for $$CREATE_ROOT_DICT_FOR_CLASSES classes"
QMAKE_EXTRA_TARGETS += rootcintecho rootcint
QMAKE_CLEAN       +=  src/$${ROOT_CINT_TARGET}Dict.cpp src/$${ROOT_CINT_TARGET}Dict.h




