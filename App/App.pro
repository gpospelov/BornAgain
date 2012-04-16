TEMPLATE = app
CONFIG  += console
CONFIG  -= qt
CONFIG  -= app_bundle
QT      -= core gui

SOURCES += \
    src/main.cpp \
    src/TestFresnelCoeff.cpp

HEADERS += \
    inc/TestFresnelCoeff.h

INCLUDEPATH += ./inc

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


###############################################################################
# adding ROOT libraries
# the problem here is that system variables doesn;t propagate
# into QtCreator
###############################################################################
exists($$(ROOTSYS)/bin/root-config){
  INCLUDEPATH += $$system($ROOTSYS/bin/root-config --incdir)
  LIBS += $$system($ROOTSYS/bin/root-config --glibs)
}
!exists($$(ROOTSYS)/bin/root-config){
  INCLUDEPATH += /opt/local/include/root
  LIBS +=  -L/opt/local/lib/root -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lm -ldl
}


###############################################################################
# Hand made addition to generate root dictionaries in the
# absence of rootcint.pri file
###############################################################################
#CREATE_ROOT_DICT_FOR_CLASSES = TestLogos.h TestLogosLinkDef.h
#
#DICTDEFINES += -DQT_VERSION=0x30000
#QT_VERSION=$$[QT_VERSION]
#contains( QT_VERSION, "^4.*" ) {
#  DICTDEFINES -= -DQT_VERSION=0x30000
#  DICTDEFINES *= -DQT_VERSION=0x40000
#}
#ROOT_CINT_TARGET = $${TARGET}
#SOURCES         *= $${ROOT_CINT_TARGET}Dict.cpp
#rootcint.target       = $${ROOT_CINT_TARGET}Dict.cpp
#rootcint.commands    += /opt/local/bin/rootcint
#rootcint.commands    +=  -f $$rootcint.target  -c -p $$DICTDEFINES $(INCPATH) $$CREATE_ROOT_DICT_FOR_CLASSES
#rootcint.depends      = $$CREATE_ROOT_DICT_FOR_CLASSES
#
#rootcintecho.commands = @echo "Generating dictionary $$rootcint.target for $$CREATE_ROOT_DICT_FOR_CLASSES classes"
#QMAKE_EXTRA_TARGETS += rootcintecho rootcint
#QMAKE_CLEAN       +=  $${ROOT_CINT_TARGET}Dict.cpp $${ROOT_CINT_TARGET}Dict.h



