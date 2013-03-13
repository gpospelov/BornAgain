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
    $${FUNCTIONAL_TESTS}/IsGISAXS01/IsGISAXS01.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS02/IsGISAXS02.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS03/IsGISAXS03.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS04/IsGISAXS04.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS06/IsGISAXS06.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS07/IsGISAXS07.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS08/IsGISAXS08.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS09/IsGISAXS09.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS10/IsGISAXS10.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS11/IsGISAXS11.cpp \
    $${FUNCTIONAL_TESTS}/IsGISAXS15/IsGISAXS15.cpp \
    src/AppOptionsDescription.cpp \
    src/CommandLine.cpp \
    src/DrawHelper.cpp \
    src/FitSuiteObserverFactory.cpp \
    src/FunctionalTestFactory.cpp \
    src/IFunctionalTest.cpp \
    src/IsGISAXSData.cpp \
    src/IsGISAXSTools.cpp \
    src/MinimizerFactory.cpp \
    src/ROOTGSLNLSMinimizer.cpp \
    src/ROOTGSLSimAnMinimizer.cpp \
    src/ROOTMinimizer.cpp \
    src/ROOTMinimizerHelper.cpp \
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
    src/TestFresnelCoeff.cpp \
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
    src/TestRootTree.cpp \
    src/TestRoughness.cpp \
    src/TestToySimulation.cpp \
    src/TreeEventStructure.cpp \
    src/main.cpp

HEADERS += \
    $${FUNCTIONAL_TESTS}/IsGISAXS01/IsGISAXS01.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS02/IsGISAXS02.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS03/IsGISAXS03.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS04/IsGISAXS04.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS06/IsGISAXS06.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS07/IsGISAXS07.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS08/IsGISAXS08.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS09/IsGISAXS09.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS10/IsGISAXS10.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS11/IsGISAXS11.h \
    $${FUNCTIONAL_TESTS}/IsGISAXS15/IsGISAXS15.h \
    inc/App.h \
    inc/AppLinkDef.h \
    inc/AppOptionsDescription.h \
    inc/CommandLine.h \
    inc/DrawHelper.h \
    inc/FitSuiteObserverFactory.h \
    inc/FunctionalTestFactory.h \
    inc/IFunctionalTest.h \
    inc/IsGISAXSData.h \
    inc/IsGISAXSTools.h \
    inc/MinimizerFactory.h \
    inc/ROOTGSLNLSMinimizer.h \
    inc/ROOTGSLSimAnMinimizer.h \
    inc/ROOTMinimizer.h \
    inc/ROOTMinimizerFunction.h \
    inc/ROOTMinimizerHelper.h \
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
    inc/TestFresnelCoeff.h \
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
    inc/TestRootTree.h \
    inc/TestRoughness.h \
    inc/TestToySimulation.h \
    inc/TreeEventStructure.h \
    inc/Version.h \

# to throw exception in the case floating point exception
CONFIG(DEBUG_FPE) {
   QMAKE_CXXFLAGS_DEBUG += -DDEBUG_FPE
   # mac requires his own patched version of fp_exceptions
   macx:HEADERS += inc/fp_exception_glibc_extension.h
   macx:SOURCES += src/fp_exception_glibc_extension.c
}

LOCATIONS = $$PWD/inc \
            $${FUNCTIONAL_TESTS}/IsGISAXS01 \
            $${FUNCTIONAL_TESTS}/IsGISAXS02 \
            $${FUNCTIONAL_TESTS}/IsGISAXS03 \
            $${FUNCTIONAL_TESTS}/IsGISAXS04 \
            $${FUNCTIONAL_TESTS}/IsGISAXS06 \
            $${FUNCTIONAL_TESTS}/IsGISAXS07 \
            $${FUNCTIONAL_TESTS}/IsGISAXS08 \
            $${FUNCTIONAL_TESTS}/IsGISAXS09 \
            $${FUNCTIONAL_TESTS}/IsGISAXS10 \
            $${FUNCTIONAL_TESTS}/IsGISAXS11 \
            $${FUNCTIONAL_TESTS}/IsGISAXS15

INCLUDEPATH += $${LOCATIONS}
DEPENDPATH  += $${LOCATIONS}

OBJECTS_DIR = obj

# -----------------------------------------------------------------------------
# generating package dependency flags
# -----------------------------------------------------------------------------
MY_DEPENDENCY_LIB = BornAgainCore
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
  MYROOTCINT = $${MYROOT}/bin/rootcint

  # checking existence of necessary set of ROOT libraries
  #LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lMathMore -lMinuit2 -lGeom -lEve -lRGL -lThread -lpthread -lm -ldl
  LIBS += -L$$system($${MYROOT}/bin/root-config --libdir )
  REQUIRED_ROOT_LIBS = Gui Core Cint RIO Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore MathMore Minuit2 Geom Eve RGL Thread

  for(x, REQUIRED_ROOT_LIBS) {
    libfile = $$system($${MYROOT}/bin/root-config --libdir )/lib$${x}.so
    !exists($${libfile}) : MISSED_ROOT_LIBRARIES += $${libfile}
    LIBS += -l$${x}
  }
  !isEmpty(MISSED_ROOT_LIBRARIES) {
    message("Error! Following ROOT libraries are missed: $${MISSED_ROOT_LIBRARIES}")
    message("Please install them before proceed. If you are compiling ROOT by yourself, use \'configure --all\' option.")
    error("Program will not link, exiting...")
  }
}
LIBS += -lpthread -lm -ldl

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
QMAKE_DISTCLEAN  += $$PWD/obj/*.o




