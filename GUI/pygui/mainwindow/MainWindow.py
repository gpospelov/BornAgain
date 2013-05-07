import sys
import os
import sip

from PyQt4.QtCore import (
    Qt, QObject, QString
)

from PyQt4.QtGui import (
    QApplication, qApp, QMainWindow, QWidget, QIcon, QColor, QStyle
)

sys.path.append(os.path.abspath("../../lib"))
sys.path.append(os.path.abspath(".."))


def toPyQt(object, type):
    ptr = object.unwrap()
    return sip.wrapinstance(ptr, type)

def fromPyQt(object, type):
    ptr = sip.unwrapinstance(object)
    return type.wrap(ptr)


#import ManhattanStyle as lms
import libManhattanStyle as lms
from views.WelcomeView import WelcomeView

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)

        baseName = QApplication.style().objectName()

        #manhattan_style = lms.ManhattanStyle( str(baseName) )
        #manhattan_style = lms.ManhattanStyle( sip.unwrapinstance(baseName) )
        #manhattan_style = lms.ManhattanStyle( fromPyQt(baseName, lms.QString) )

        #lms.StyleHelper.setBaseColor( fromPyQt(QColor(0x086FA1), lms.QColor) )

        #k = QColor(Qt.red)
        #lms.StyleHelper.setBaseColor(k )
        #qApp.setStyle( lms.toPyQt(manhattan_style) )

        self.__tabWidget = lms.FancyTabWidget(self)
        self.__welcomeView = WelcomeView()

        print "PPPPP 1.1"
        self.__tabWidget.insertTab(0, self.__welcomeView,  QIcon("images/mode_welcome.png"), "Welcome" )
        print "PPPPP 1.2"
        #self.__tabWidget.insertTab(0, fromPyQt(self.__welcomeView, lms.QWidget), fromPyQt(QIcon(":/images/mode_welcome.png"), lms.QIcon), fromPyQt(QString("Welcome"), lms.QString ))

        self.setCentralWidget( lms.toPyQt(self.__tabWidget) )
        #self.setCentralWidget( self.__welcomeView )



