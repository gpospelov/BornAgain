TEMPLATE = app
CONFIG  += console
CONFIG  -= qt app_bundle
QT      -= core gui

include($$PWD/../../../../shared.pri)
DEFINES += STANDALONE

INCLUDEPATH *= $$EIGEN_INCLUDE_DIR
INCLUDEPATH *= $$BOOST_INCLUDE_DIR
INCLUDEPATH += $$BornAgainCore_INCLUDE_DIR
LIBS += $$BOOST_LIBRARY $$BornAgainCore_LIBRARY

SOURCES += IsGISAXS15.cpp
HEADERS += IsGISAXS15.h

