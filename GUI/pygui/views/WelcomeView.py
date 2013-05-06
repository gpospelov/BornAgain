from PyQt4.QtCore import (
    QObject,
)

from PyQt4.QtGui import (
    QMainWindow, QWidget, 
)


class WelcomeView(QWidget):
    def __init__(self, parent = None):
        QWidget.__init__(self, parent)
