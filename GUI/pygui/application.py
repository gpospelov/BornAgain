import sys
import os
from PyQt4.QtGui import QApplication, QMainWindow

from mainwindow.MainWindow import MainWindow


def main():
    a = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    return a.exec_()


if __name__ == "__main__":
    sys.exit(main())
