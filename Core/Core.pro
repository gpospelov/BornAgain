TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += src/main.cpp \
    src/NanoParticle.cpp \
    src/Layer.cpp \
    src/HomogeneousMaterial.cpp \
    src/MultiLayer.cpp \
    src/LayerRoughness.cpp \
    src/Exceptions.cpp \
    src/ISample.cpp

HEADERS += \
    inc/ISample.h \
    inc/NanoParticle.h \
    inc/Layer.h \
    inc/IMaterial.h \
    inc/HomogeneousMaterial.h \
    inc/MultiLayer.h \
    inc/LayerRoughness.h \
    inc/Exceptions.h

