# -----------------------------------------------------------------------------
# qmake project file to compile libBornAgainFit
# -----------------------------------------------------------------------------
TARGET   = BornAgainFit
TEMPLATE = lib
QT      -= core gui
macx|unix {
  QMAKE_EXTENSION_SHLIB = so # making standard *.so extension
  CONFIG  += plugin # to remove versions from file name
}
#CONFIG  += BORNAGAIN_PYTHON
CONFIG  += BORNAGAIN_ROOT

# -----------------------------------------------------------------------------
# common project settings
# -----------------------------------------------------------------------------
include($$PWD/../shared.pri)

# -----------------------------------------------------------------------------
# source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    Factory/src/MinimizerFactory.cpp \
    Factory/src/ROOTGSLNLSMinimizer.cpp \
    Factory/src/ROOTGSLSimAnMinimizer.cpp \
    Factory/src/ROOTMinimizer.cpp \
    Factory/src/ROOTMinimizerHelper.cpp \
    #Factory/src/FitSuiteObserverFactory.cpp \
    #Factory/src/FitSuitePrintObserver.cpp \
    #Factory/src/FitSuiteDrawObserver.cpp \
    #Factory/src/FitSuiteWriteTreeObserver.cpp
    Factory/src/GSLMinimizer.cxx \
    Factory/src/GSLMinimizer1D.cxx \
    Factory/src/MultiNumGradFunction.cxx \
    Factory/src/GSLSimAnnealing.cxx \
    Factory/src/GSLRndmEngines.cxx \
    Factory/src/Derivator.cxx \
    Factory/src/GSLDerivator.cxx

HEADERS += \
    Factory/inc/MinimizerFactory.h \
    Factory/inc/ROOTGSLNLSMinimizer.h \
    Factory/inc/ROOTGSLSimAnMinimizer.h \
    Factory/inc/ROOTMinimizer.h \
    Factory/inc/ROOTMinimizerFunction.h \
    Factory/inc/ROOTMinimizerHelper.h \
    #Factory/inc/FitSuiteObserverFactory.h \
    #Factory/inc/FitSuitePrintObserver.h \
    #Factory/inc/FitSuiteDrawObserver.h \
    #Factory/inc/FitSuiteWriteTreeObserver.h
    Factory/inc/GSLMinimizer.h \
    Factory/inc/GSLMinimizer1D.h \
    Factory/inc/GSLSimAnnealing.h \
    Factory/inc/GSLMultiFitFunctionWrapper.h \
    Factory/inc/GSLMultiFitFunctionAdapter.h \
    Factory/inc/GSLMultiFit.h \
    Factory/inc/GSLMultiMinimizer.h \
    Factory/inc/GSLMultiMinFunctionWrapper.h \
    Factory/inc/GSLMultiMinFunctionAdapter.h \
    Factory/inc/GSLFunctionWrapper.h \
    Factory/inc/MultiNumGradFunction.h \
    Factory/inc/GSLRngWrapper.h \
    Factory/inc/GSLRndmEngines.h \
    Factory/inc/MultiNumGradFunction.h \
    Factory/inc/Derivator.h \
    Factory/inc/GSLDerivator.h



INCLUDEPATH += $$PWD/Factory/inc
DEPENDPATH  += $$PWD/Factory/inc

contains(CONFIG, BORNAGAIN_PYTHON) {
   include($$PWD/python_module.pri)
}

# -----------------------------------------------------------------------------
# additional libraries
# -----------------------------------------------------------------------------
LIBS += $$PWD/../lib/libBornAgainCore.$${SONAME}

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
QMAKE_POST_LINK = (make install)



