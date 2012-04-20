###############################################################################
# qmake project file to compile shared library
###############################################################################
TARGET   = ScattCore
TEMPLATE = lib
CONFIG  += plugin # to remove versions from file name
QT      -= core gui

QMAKE_EXTENSION_SHLIB = so

SOURCES += \
    src/NanoParticle.cpp \
    src/Layer.cpp \
    src/HomogeneousMaterial.cpp \
    src/MultiLayer.cpp \
    src/LayerRoughness.cpp \
    src/Exceptions.cpp \
    src/ISample.cpp \
    src/IAlgorithm.cpp \
    src/CalculatorOptical.cpp \
    src/ISimulation.cpp \
    src/OutputData.cpp \
    src/OpticalFresnel.cpp \
    src/IRoughness.cpp \
    src/LayerInterface.cpp \
    src/IMaterial.cpp \
    src/MaterialManager.cpp \
    src/StochasticGaussian.cpp \
    src/MathFunctions.cpp \

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
    inc/Types.h \
    inc/CalculatorOptical.h \
    inc/ISimulation.h \
    inc/OutputData.h \
    inc/NamedVector.h \
    inc/OpticalFresnel.h \
    inc/IRoughness.h \
    inc/LayerInterface.h \
    inc/MaterialManager.h \
    inc/IStochasticParameter.h \
    inc/StochasticGaussian.h \
    inc/MathFunctions.h

INCLUDEPATH += ./inc

OBJECTS_DIR = obj

###############################################################################
# Installing library into dedicated directory at the end of compilation
###############################################################################
MYPREFIX = $$PWD/.. # place to install library and headers
target.path = $$MYPREFIX/lib
INSTALLS += target
includes.files = $$PWD/inc/*.h
includes.path = $$MYPREFIX/inc/ScattCore
INSTALLS += includes
# there is a soft bug here in qmake, it looks like flag '-r' works
# only when it appears at the beginning of QMAKE_DISTCLEAN variable
# i.e. the order below is important
QMAKE_DISTCLEAN += -r $$includes.path
QMAKE_DISTCLEAN += $$target.path/$(TARGET)

QMAKE_POST_LINK = (make install)

