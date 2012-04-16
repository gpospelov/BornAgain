###############################################################################
# qmake project file to compile and run unit test of ScattCore library
###############################################################################
TEMPLATE = app
CONFIG  -= qt app_bundle
CONFIG  += console build_all
QT      -= core gui

SOURCES += main.cpp

HEADERS += \
    NamedVectorTest.h \
    OutputDataTest.h

OBJECTS_DIR = obj


###############################################################################
# generating package dependency flags
###############################################################################
MY_DEPENDENCY_LIB = gtest ScattCore
MY_DEPENDENCY_DEST =$$PWD/../..
SONAME = so
INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc/$${dep}
}


# some hack that might be required for linux... under investigation
#LIBS += -lpthread
#LDFLAGS = -L/lib64
#QMAKE_CXXFLAGS += -pthread



###############################################################################
# attempt to compile project dependencies not from the top
###############################################################################
#PRE_TARGETDEPS += $$PWD/../../ThirdParty/gtest/libgtest.a
#makelibs.target = $$PWD/../../ThirdParty/gtest/libgtest.a
#makelibs.commands = (cd $$PWD/../../ThirdParty/gtest; qmake; make)
#makelibs.depends = FORCE
#QMAKE_EXTRA_TARGETS += makelibs


###############################################################################
# runs automatically tests right after linking
###############################################################################
QMAKE_POST_LINK = ./$(TARGET)
