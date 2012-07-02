TEMPLATE = app
CONFIG  += console
CONFIG  -= qt
CONFIG  -= app_bundle
CONFIG  += debug
QT      -= core gui

SOURCES += \
    src/main.cpp \
    src/CommandLine.cpp \
    src/DrawHelper.cpp \
    src/IFunctionalTest.cpp \
    src/IsGISAXSTools.cpp \
    src/SampleFactory.cpp \
    src/StandardSamples.cpp \
    src/TestConvolution.cpp \
    src/TestDiffuseReflection.cpp \
    src/TestFactory.cpp \
    src/TestFormFactor.cpp \
    src/TestFresnelCoeff.cpp \
    src/TestIsGISAXS1.cpp \
    src/TestIsGISAXS3.cpp \
    src/TestIsGISAXS10.cpp \
    src/TestRoughness.cpp \

HEADERS += \
    inc/App.h \
    inc/AppLinkDef.h \
    inc/CommandLine.h \
    inc/DrawHelper.h \
    inc/IFunctionalTest.h \
    inc/IsGISAXSTools.h \
    inc/SampleFactory.h \
    inc/StandardSamples.h \
    inc/TestConvolution.h \
    inc/TestDiffuseReflection.h \
    inc/TestFactory.h \
    inc/TestFormFactor.h \
    inc/TestFresnelCoeff.h \
    inc/TestIsGISAXS1.h \
    inc/TestIsGISAXS3.h \
    inc/TestIsGISAXS10.h \
    inc/TestRoughness.h \

INCLUDEPATH += ./inc ../Core/Algorithms/inc ../Core/Samples/inc ../Core/Tools/inc
DEPENDPATH += ./inc ../Core/Algorithms/inc ../Core/Samples/inc ../Core/Tools/inc

OBJECTS_DIR = obj

###############################################################################
# generating package dependency flags
###############################################################################
MY_DEPENDENCY_LIB = ScattCore
MY_DEPENDENCY_DEST =$$PWD/..
SONAME = so
INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc/$${dep}
}

macx {
  INCLUDEPATH += /opt/local/include
  LIBS += -L /opt/local/lib/ -lfftw3
} else {
  LIBS += -L /usr/lib64/ -lfftw3
}

###############################################################################
# adding ROOT libraries
# the problem here is that system variables doesn;t propagate
# into QtCreator
###############################################################################
exists($$(ROOTSYS)/bin/root-config){
  INCLUDEPATH += $$system($ROOTSYS/bin/root-config --incdir)
  #LIBS += $$system($ROOTSYS/bin/root-config --glibs)
  LIBS += -L$$system($ROOTSYS/bin/root-config --libdir ) -lGui -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad  -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lm -ldl

  MYROOTCINT = ${ROOTSYS}/bin/rootcint
}
!exists($$(ROOTSYS)/bin/root-config){
  INCLUDEPATH += /opt/local/include/root
  LIBS +=  -L/opt/local/lib/root -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lm -ldl
  MYROOTCINT = /opt/local/bin/rootcint
}


###############################################################################
# Hand made addition to generate root dictionaries in the
# absence of rootcint.pri file
###############################################################################
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
rootcint.commands    +=  -f $$rootcint.target  -c -p $$DICTDEFINES $(INCPATH) $$CREATE_ROOT_DICT_FOR_CLASSES
rootcint.depends      = $$CREATE_ROOT_DICT_FOR_CLASSES

rootcintecho.commands = @echo "Generating dictionary $$rootcint.target for $$CREATE_ROOT_DICT_FOR_CLASSES classes"
QMAKE_EXTRA_TARGETS += rootcintecho rootcint
QMAKE_CLEAN       +=  src/$${ROOT_CINT_TARGET}Dict.cpp src/$${ROOT_CINT_TARGET}Dict.h




