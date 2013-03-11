CONFIG  += console
CONFIG  -= qt
CONFIG  -= app_bundle
QT      -= core gui

include($$PWD/../../../shared.pri)

###############################################################################
# generating package dependency flags
###############################################################################
MY_DEPENDENCY_LIB = BornAgainCore
MY_DEPENDENCY_DEST =$$PWD/../../..
SONAME = so
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
}

QMAKE_CXXFLAGS_RELEASE += -DSTANDALONE
QMAKE_CXXFLAGS_DEBUG += -DSTANDALONE

