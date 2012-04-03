TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    nanoparticle.cpp \
    layer.cpp \
    homogeneousmaterial.cpp \
    multilayer.cpp \
    layerroughness.cpp \
    exceptions.cpp

HEADERS += \
    isample.h \
    nanoparticle.h \
    layer.h \
    imaterial.h \
    homogeneousmaterial.h \
    multilayer.h \
    layerroughness.h \
    exceptions.h

