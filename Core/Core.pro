TEMPLATE = app
CONFIG += console
CONFIG -= qt

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
    src/OutputData.cpp

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
    inc/NamedVector.h

INCLUDEPATH += ./inc

OTHER_FILES += \
    Makefile.am

OBJECTS_DIR = obj

# bla bla 1
# bla bla 2
