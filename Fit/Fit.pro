# -----------------------------------------------------------------------------
# qmake project file to compile libBornAgainFit
# -----------------------------------------------------------------------------
TARGET   = BornAgainFit

TEMPLATE = lib
QT      -= core gui
macx|unix {
  CONFIG  += plugin # to remove versions from file name
}

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

contains(CONFIG, BORNAGAIN_PYTHON) {
   include($$PWD/python_module.pri)
}

win32 {
    DEFINES += BA_CORE_BUILD_DLL
}

# -----------------------------------------------------------------------------
# dependencies
# -----------------------------------------------------------------------------
INCLUDEPATH *= $$GSL_INCLUDE_DIR
INCLUDEPATH *= $$BOOST_INCLUDE_DIR
INCLUDEPATH *= $$EIGEN_INCLUDE_DIR
INCLUDEPATH += $$BornAgainFit_INCLUDE_DIR
INCLUDEPATH += $$BornAgainCore_INCLUDE_DIR
INCLUDEPATH += $$RootMinimizers_INCLUDE_DIR
INCLUDEPATH += $$PYTHON_INCLUDE_DIR
LIBS += $$BOOST_LIBRARY $$GSL_LIBRARY $$BornAgainCore_LIBRARY $$RootMinimizers_LIBRARY $$PYTHON_LIBRARY

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
isEmpty(MAKEFILE): MAKEFILE="Makefile"

# for python import in Windows we need another extention and preffix
win32{
    extra_install.path = $$PWD\..\lib
    extra_install.extra = $(COPY) /y \"BornAgainFit.dll\" \"libBornAgainFit.pyd\"
    extra_install.files = $$PWD\libBornAgainFit.pyd
    INSTALLS += extra_install
}

QMAKE_POST_LINK+= $$MAKE_COMMAND -f $${MAKEFILE} install

