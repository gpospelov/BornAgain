# Application visual style as in qt-creator, taken from https://github.com/tegesoft/qt-manhattan
TARGET = ManhattanStyle
TEMPLATE = lib

QT += core gui webkit webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# making standard shared library extension
QMAKE_EXTENSION_SHLIB = so
CONFIG  += plugin # to remove versions from file name

# The code still used some deprecated stuff
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x040900

#LIBS -= U/sers/pospelov/nest/software/Qt5.0.1/5.0.1/clang_64/qtbase/lib

DEFINES += QTMANHATTANSTYLE_LIBRARY

INCLUDEPATH += src

SOURCES += \
    stylehelper.cpp \
    styledbar.cpp \
    styleanimator.cpp \
    stringutils.cpp \
    qtcolorbutton.cpp \
    qtcassert.cpp \
    progressbar.cpp \
    minisplitter.cpp \
    manhattanstyle.cpp \
    historycompleter.cpp \
    fancytabwidget.cpp \
    fancymainwindow.cpp \
    fancylineedit.cpp \
    fancyactionbar.cpp \
    doubletabwidget.cpp \
    extensions/simpleprogressbar.cpp \
    extensions/tabwidget.cpp \
    extensions/threelevelsitempicker.cpp \

HEADERS +=\
    stylehelper.h \
    styledbar.h \
    styleanimator.h \
    stringutils.h \
    qtcolorbutton.h \
    qtcolorbutton_p.h \
    qtcassert.h \
    progressbar.h \
    minisplitter.h \
    manhattanstyle.h \
    historycompleter.h \
    fancytabwidget.h \
    fancymainwindow.h \
    fancylineedit.h \
    fancyactionbar.h \
    doubletabwidget.h \
    coreconstants.h \
    qt-manhattan-style_global.hpp \
    extensions/simpleprogressbar.h \
    extensions/tabwidget.h \
    extensions/threelevelsitempicker.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    doubletabwidget.ui

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += \
    CMakeLists.txt


#pythonvers=$$system("python -c 'import sys; sys.stdout.write(sys.version[:3])'")
#pythonsysincdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/include/python\" + sys.version[:3])'")
#pythonsyslibdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/lib\" )'")
#INCLUDEPATH += $$pythonsysincdir
#LIBS += -lboost_python -L$$pythonsyslibdir -lpython$$pythonvers

# -----------------------------------------------------------------------------
# general project settings
# -----------------------------------------------------------------------------

CONFIG  += BORNAGAIN_PYTHON
include($$PWD/../../../shared.pri)
INCLUDEPATH -= /opt/local/include

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../../../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
QMAKE_POST_LINK = (make install)

