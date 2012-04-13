TEMPLATE = app

CONFIG += console
CONFIG -= qt
CONFIG -= app_bundle

QT       -= core
QT       -= gui

SOURCES += src/main.cpp \
    src/NanoParticle.cpp \
    src/Layer.cpp \
    src/HomogeneousMaterial.cpp \
    src/MultiLayer.cpp \
    src/LayerRoughness.cpp \
    src/Exceptions.cpp \
    src/ISample.cpp \
    src/IAlgorithm.cpp \
    src/TestFresnelCoeff.cpp \
    src/CalculatorOptical.cpp \
    src/ISimulation.cpp \
    src/OutputData.cpp \
    src/OpticalFresnel.cpp

HEADERS += \
    inc/ISample.h \
    inc/NanoParticle.h \
    inc/Layer.h \
    inc/IMaterial.h \
    inc/HomogeneousMaterial.h \
    inc/MultiLayer.h \
    inc/LayerRoughness.h \
    inc/Exceptions.h \
    inc/IAlgorithm.h \
    inc/TestFresnelCoeff.h \
    inc/Types.h \
    inc/CalculatorOptical.h \
    inc/ISimulation.h \
    inc/OutputData.h \
    inc/NamedVector.h \
    inc/OpticalFresnel.h

INCLUDEPATH += ./inc

OTHER_FILES += \
    Makefile.am

OBJECTS_DIR = obj

#############################################################
# adding ROOT libraries
#############################################################
#INCLUDEPATH += /opt/local/include/root
#LIBS +=  -L/opt/local/lib/root -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lpthread -lm -ldl
INCLUDEPATH += $$system(root-config --incdir)
LIBS += $$system(root-config --libdir)


#############################################################
# Hand made addition to generate root dictionaries in the
# absence of rootcint.pri file
#############################################################
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



