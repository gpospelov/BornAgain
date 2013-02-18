TARGET = GQt

TEMPLATE = lib 
CONFIG  += plugin
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_EXTENSION_SHLIB = so


GQTDIRI = inc
GQTDIRS = src

OBJECTS_DIR = obj
#UI_DIR = .ui
#MOC_DIR = .moc

# Input
HEADERS += $$GQTDIRI/TGQt.h \
           $$GQTDIRI/TObjectExecute.h \
           $$GQTDIRI/TQMimeTypes.h \
           $$GQTDIRI/TQtApplication.h \
           $$GQTDIRI/TQtBrush.h \
           $$GQTDIRI/TQtClientFilter.h \
           $$GQTDIRI/TQtClientGuard.h \
           $$GQTDIRI/TQtClientWidget.h \
           $$GQTDIRI/TQtEvent.h \
           $$GQTDIRI/TQtEventQueue.h \
           $$GQTDIRI/TQtMarker.h \
           $$GQTDIRI/TQtRConfig.h \
           $$GQTDIRI/TQtRootApplication.h \
           $$GQTDIRI/TQtSymbolCodec.h \
           $$GQTDIRI/TQtTimer.h \
           $$GQTDIRI/TQtUtil.h \
           $$GQTDIRI/TQtWidget.h \
           $$GQTDIRI/TQUserEvent.h \
           $$GQTDIRI/TVirtualX.interface.h  \
           $$GQTDIRI/TWaitCondition.h       \
           $$GQTDIRI/TQtLock.h              \
           $$GQTDIRI/TQtEmitter.h           \
           $$GQTDIRI/TQtLockGuard.h         \
           $$GQTDIRI/TQtPadFont.h           \
           $$GQTDIRI/TQtPen.h               \
           $$GQTDIRI/TQtCanvasPainter.h     \
           $$GQTDIRI/TQtRootSlot.h

SOURCES += $$GQTDIRS/GQtGUI.cxx             \
           $$GQTDIRS/TGQt.cxx               \
           $$GQTDIRS/TGQtDummy.cxx          \
           $$GQTDIRS/TQMimeTypes.cxx        \
           $$GQTDIRS/TQtApplication.cxx     \
           $$GQTDIRS/TQtBrush.cxx           \
           $$GQTDIRS/TQtClientFilter.cxx    \
           $$GQTDIRS/TQtClientGuard.cxx     \
           $$GQTDIRS/TQtClientWidget.cxx    \
           $$GQTDIRS/TQtEvent.cxx           \
           $$GQTDIRS/TQtEventQueue.cxx      \
           $$GQTDIRS/TQtMarker.cxx          \
           $$GQTDIRS/TQtRootApplication.cxx \
           $$GQTDIRS/TQtSymbolCodec.cxx     \
           $$GQTDIRS/TQtTimer.cxx           \
           $$GQTDIRS/TQtWidget.cxx          \
           $$GQTDIRS/TQtPadFont.cxx         \
           $$GQTDIRS/TQtPen.cxx             \
           $$GQTDIRS/TQtRootSlot.cxx

INCLUDEPATH += $$GQTDIRI
DEPENDPATH  += $$GQTDIRI

# -----------------------------------------------------------------------------
# adding ROOT libraries
# -----------------------------------------------------------------------------
MYROOT = $$(ROOTSYS)
isEmpty(MYROOT) {
  message("Warning, ROOTSYS environment variable doesn't exist, trying to guess location")
  ROOT_CONFIG_FILE = root-config
  ROOT_CONFIG_FILE_LOCATIONS = /opt/local /usr/local /usr
  for(dir, ROOT_CONFIG_FILE_LOCATIONS): isEmpty(MYROOT): exists($${dir}/bin/$${ROOT_CONFIG_FILE}): MYROOT = $${dir}
  isEmpty(MYROOT): error("Can't find" $${ROOT_CONFIG_FILE} "in" $${ROOT_CONFIG_FILE_LOCATIONS})
  message("Probable ROOTSYS is" $${MYROOT})
}
!isEmpty(MYROOT) {
  !exists($${MYROOT}/bin/root-config): error("No config file "$${MYROOT}/bin/root-config)
  INCLUDEPATH += $$system($${MYROOT}/bin/root-config --incdir)
  #LIBS += $$system($${MYROOT}/bin/root-config --glibs )
  LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lGraf -lGpad -lRint -lpthread -lm -ldl
  MYROOTCINT = $${MYROOT}/bin/rootcint
}

# -----------------------------------------------------------------------------
# Hand made addition to generate root dictionaries in the
# absence of rootcint.pri file
# -----------------------------------------------------------------------------
GQTH1  =  $$GQTDIRI/TGQt.h            $$GQTDIRI/TQtApplication.h  $$GQTDIRI/TQtTimer.h    \
          $$GQTDIRI/TQtBrush.h        $$GQTDIRI/TQMimeTypes.h $$GQTDIRI/TQtClientFilter.h \
          $$GQTDIRI/TQtClientWidget.h $$GQTDIRI/TQtWidget.h   $$GQTDIRI/TQtMarker.h       \
          $$GQTDIRI/TQtRootSlot.h     $$GQTDIRI/TQtPadFont.h

CREATE_ROOT_DICT_FOR_CLASSES  = $$GQTH1 $$GQTDIRI/LinkDef.h

DICTDEFINES += -DQT_VERSION=0x50000
QT_VERSION=$$[QT_VERSION]
contains( QT_VERSION, "^4.*" ) {
  DICTDEFINES -= -DQT_VERSION=0x50000
  DICTDEFINES *= -DQT_VERSION=0x40000
}
ROOT_CINT_TARGET = $${TARGET}
SOURCES         *= src/$${ROOT_CINT_TARGET}Dict.cpp
rootcint.target       = src/$${ROOT_CINT_TARGET}Dict.cpp
rootcint.commands    += $$MYROOTCINT
rootcint.commands    +=  -f $$rootcint.target  -c -I./inc $$CREATE_ROOT_DICT_FOR_CLASSES
#rootcint.commands    +=  -f $$rootcint.target  -c -p $$DICTDEFINES $(INCPATH) $$CREATE_ROOT_DICT_FOR_CLASSES
rootcint.depends      = $$CREATE_ROOT_DICT_FOR_CLASSES

rootcintecho.commands = @echo "Generating dictionary $$rootcint.target for $$CREATE_ROOT_DICT_FOR_CLASSES classes"
QMAKE_EXTRA_TARGETS += rootcintecho rootcint
QMAKE_CLEAN       +=  src/$${ROOT_CINT_TARGET}Dict.cpp src/$${ROOT_CINT_TARGET}Dict.h
QMAKE_DISTCLEAN  += $$PWD/obj/*.o

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../../../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
QMAKE_DISTCLEAN  += $$PWD/obj/*.o
QMAKE_POST_LINK = (make install)
