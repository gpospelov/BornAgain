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
CONFIG  += BORNAGAIN_ROOT

# -----------------------------------------------------------------------------
# common project settings
# -----------------------------------------------------------------------------
include($$PWD/../shared.pri)

# -----------------------------------------------------------------------------
# source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    Factory/src/FitObject.cpp \
    Factory/src/FitParameter.cpp \
    Factory/src/FitParameterLinked.cpp \
    Factory/src/FitSuite.cpp \
    Factory/src/FitSuiteFunctions.cpp \
    Factory/src/FitSuiteObjects.cpp \
    Factory/src/FitSuiteParameters.cpp \
    Factory/src/FitSuitePrintObserver.cpp \
    Factory/src/FitSuiteStrategies.cpp \
    Factory/src/IFitSuiteStrategy.cpp \
    Factory/src/MinimizerFactory.cpp \
    Factory/src/MinimizerScan.cpp \
    Factory/src/MinimizerTest.cpp \
    Factory/src/ROOTGSLNLSMinimizer.cpp \
    Factory/src/ROOTGSLSimAnMinimizer.cpp \
    Factory/src/ROOTMinimizer.cpp \
    Factory/src/ROOTMinimizerHelper.cpp \

HEADERS += \
    Factory/inc/AttFitting.h \
    Factory/inc/AttLimits.h \
    Factory/inc/FitObject.h \
    Factory/inc/FitParameter.h \
    Factory/inc/FitParameterLinked.h \
    Factory/inc/FitSuite.h \
    Factory/inc/FitSuiteFunctions.h \
    Factory/inc/FitSuiteObjects.h \
    Factory/inc/FitSuiteParameters.h \
    Factory/inc/FitSuitePrintObserver.h \
    Factory/inc/FitSuiteStrategies.h \
    Factory/inc/IFitSuiteStrategy.h \
    Factory/inc/IMinimizer.h \
    Factory/inc/MinimizerFactory.h \
    Factory/inc/MinimizerScan.h \
    Factory/inc/MinimizerTest.h \
    Factory/inc/ROOTGSLNLSMinimizer.h \
    Factory/inc/ROOTGSLSimAnMinimizer.h \
    Factory/inc/ROOTMinimizer.h \
    Factory/inc/ROOTMinimizerFunction.h \
    Factory/inc/ROOTMinimizerHelper.h \


INCLUDEPATH += $$PWD/Factory/inc
DEPENDPATH  += $$PWD/Factory/inc

contains(CONFIG, BORNAGAIN_PYTHON) {
   include($$PWD/python_module.pri)
}

# -----------------------------------------------------------------------------
# additional libraries
# -----------------------------------------------------------------------------
LIBS += $$PWD/../lib/libBornAgainCore.$${SONAME} $$PWD/../lib/libRootMathMore.$${SONAME}

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
QMAKE_POST_LINK = (make install)



