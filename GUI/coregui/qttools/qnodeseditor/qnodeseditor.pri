greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/qneblock.cpp \
    $$PWD/qneport.cpp \
    $$PWD/qneconnection.cpp \
    $$PWD/qnodeseditor.cpp

HEADERS  += \
    $$PWD/qneblock.h \
    $$PWD/qneport.h \
    $$PWD/qneconnection.h \
    $$PWD/qnodeseditor.h

