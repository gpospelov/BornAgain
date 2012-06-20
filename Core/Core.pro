###############################################################################
# qmake project file to compile shared library
###############################################################################
TARGET   = ScattCore
TEMPLATE = lib
CONFIG  += plugin # to remove versions from file name
CONFIG  += debug
QT      -= core gui

QMAKE_EXTENSION_SHLIB = so

SOURCES += \
    Algorithms/src/DWBADiffuseReflection.cpp \
    Algorithms/src/DWBAFormFactor.cpp \
    Algorithms/src/DWBAFormFactorConstZ.cpp \
    Algorithms/src/Experiment.cpp \
    Algorithms/src/OpticalFresnel.cpp \
    \
    Samples/src/FormFactorCylinder.cpp \
    Samples/src/HomogeneousMaterial.cpp \
    Samples/src/ICompositeIterator.cpp \
    Samples/src/ICompositeSample.cpp \
    Samples/src/IMaterial.cpp \
    Samples/src/InterferenceFunction1DParaCrystal.cpp \
    Samples/src/IRoughness.cpp \
    Samples/src/ISample.cpp \
    Samples/src/Layer.cpp \
    Samples/src/LayerInterface.cpp \
    Samples/src/LayerRoughness.cpp \
    Samples/src/MaterialManager.cpp \
    Samples/src/MultiLayer.cpp \
    Samples/src/NanoParticle.cpp \
    Samples/src/NanoParticleDecorator.cpp \
    Samples/src/ParameterPool.cpp \
    \
    Tools/src/Convolve.cpp \
    Tools/src/DoubleToComplexInterpolatingFunction.cpp \
    Tools/src/Exceptions.cpp \
    Tools/src/IFactory.cpp \
    Tools/src/INamed.cpp \
    Tools/src/ISingleton.cpp \
    Tools/src/MathFunctions.cpp \
    Tools/src/OutputData.cpp \
    Tools/src/StochasticGaussian.cpp \
    Tools/src/Types.cpp \
    Tools/src/Utils.cpp

HEADERS += \
    Algorithms/inc/DWBADiffuseReflection.h \
    Algorithms/inc/DWBAFormFactor.h \
    Algorithms/inc/DWBAFormFactorConstZ.h \
    Algorithms/inc/Experiment.h \
    Algorithms/inc/ISimulation.h \
    Algorithms/inc/OpticalFresnel.h \
    \
    Samples/inc/FormFactorCylinder.h \
    Samples/inc/HomogeneousMaterial.h \
    Samples/inc/ICompositeIterator.h \
    Samples/inc/ICompositeSample.h \
    Samples/inc/IDispersalState.h \
    Samples/inc/IFormFactor.h \
    Samples/inc/IInterferenceFunction.h \
    Samples/inc/IMaterial.h \
    Samples/inc/InterferenceFunction1DParaCrystal.h \
    Samples/inc/InterferenceFunctionNone.h \
    Samples/inc/IRoughness.h \
    Samples/inc/ISample.h \
    Samples/inc/Layer.h \
    Samples/inc/LayerInterface.h \
    Samples/inc/LayerRoughness.h \
    Samples/inc/MaterialManager.h \
    Samples/inc/MultiLayer.h \
    Samples/inc/NanoParticle.h \
    Samples/inc/NanoParticleDecorator.h \
    Samples/inc/ParameterPool.h \
    \
    Tools/inc/Convolve.h \
    Tools/inc/DoubleToComplexInterpolatingFunction.h \
    Tools/inc/Exceptions.h \
    Tools/inc/IDoubleToComplexFunction.h \
    Tools/inc/IFactory.h \
    Tools/inc/INamed.h \
    Tools/inc/ISingleton.h \
    Tools/inc/IStochasticParameter.h \
    Tools/inc/MathFunctions.h \
    Tools/inc/NamedVector.h \
    Tools/inc/Numeric.h \
    Tools/inc/OutputData.h \
    Tools/inc/StochasticDiracDelta.h \
    Tools/inc/StochasticGaussian.h \
    Tools/inc/Types.h \
    Tools/inc/Units.h \
    Tools/inc/Utils.h

INCLUDEPATH += ./Algorithms/inc ./Samples/inc ./Tools/inc
DEPENDPATH += ./Algorithms/inc ./Samples/inc ./Tools/inc

OBJECTS_DIR = obj

macx {
  INCLUDEPATH += /opt/local/include
  LIBS += -L /opt/local/lib/ -lgsl -lfftw3
} else {
  LIBS += -L /usr/lib64/ -lgsl -lgslcblas -lfftw3
}


###############################################################################
# Installing library into dedicated directory at the end of compilation
###############################################################################
MYPREFIX = $$PWD/.. # place to install library and headers
target.path = $$MYPREFIX/lib
INSTALLS += target
#includes.files = $$PWD/inc/*.h
#includes.path = $$MYPREFIX/inc/ScattCore
#INSTALLS += includes
# there is a soft bug here in qmake, it looks like flag '-r' works
# only when it appears at the beginning of QMAKE_DISTCLEAN variable
# i.e. the order below is important
#QMAKE_DISTCLEAN += -r $$includes.path
#QMAKE_DISTCLEAN += $$MYPREFIX/inc/ScattCore
QMAKE_DISTCLEAN += $$target.path/$(TARGET)


QMAKE_POST_LINK = (make install)

