TARGET   = RootMathMore
TEMPLATE = lib
QT      -= core gui
macx|unix {
  CONFIG  += plugin # to remove versions from file name
}

include(../../shared.pri)

SOURCES += \
    src/Derivator.cxx \
    src/GSLDerivator.cxx \
    src/GSLMinimizer1D.cxx \
    src/GSLMinimizer.cxx \
    src/GSLRndmEngines.cxx \
    src/GSLSimAnnealing.cxx \
    src/MultiNumGradFunction.cxx \
    src/GSLNLSMinimizer.cxx \
    src/GSLSimAnMinimizer.cxx \

HEADERS += \
    inc/Math/Derivator.h \
    inc/Math/GSLFunctionAdapter.h \
    inc/Math/GSLFunctionWrapper.h \
    inc/Math/GSLMinimizer1D.h \
    inc/Math/GSLMinimizer.h \
    inc/Math/GSLRndmEngines.h \
    inc/Math/GSLSimAnnealing.h \
    inc/Math/MultiNumGradFunction.h \
    inc/Math/GSLNLSMinimizer.h \
    inc/Math/GSLSimAnMinimizer.h \
    \
    src/GSL1DMinimizerWrapper.h \
    src/GSLDerivator.h \
    src/GSLFunctionWrapper.h \
    src/GSLMultiFitFunctionAdapter.h \
    src/GSLMultiFitFunctionWrapper.h \
    src/GSLMultiFit.h \
    src/GSLMultiMinFunctionAdapter.h \
    src/GSLMultiMinFunctionWrapper.h \
    src/GSLMultiMinimizer.h \
    src/GSLRngWrapper.h \

INCLUDEPATH +=  $$PWD/inc
DEPENDPATH  +=  $$PWD/inc

isEmpty(ROOT_FRAMEWORK) {
    INCLUDEPATH += $$RootMinimizers_INCLUDEPATH
    LIBS += $${RootMinimizers_LIB}
} else {
    INCLUDEPATH += $$ROOT_FRAMEWORK_INCLUDEPATH
    LIBS += $${ROOT_FRAMEWORK_LIBS}
}

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
isEmpty(MAKEFILE): MAKEFILE="Makefile"
QMAKE_POST_LINK = $$MAKE_COMMAND -f $${MAKEFILE} install
