from PyQt4.QtCore import (
    QObject, QUrl, SIGNAL, SLOT
)

from PyQt4.QtGui import (
    QMainWindow, QWidget, QDesktopServices
)

from PyQt4.QtWebKit import (
    QWebPage, QWebView
)


# class WelcomeView(QWidget):
#     def __init__(self, parent = None):
#         QWidget.__init__(self, parent)

class WelcomeView(QWebView):
    def __init__(self, parent = None):
        super(WelcomeView, self).__init__(parent)
        self.url = QUrl("http://apps.jcns.fz-juelich.de/doku/sc/bornagain::start")
        self.load(self.url)
        self.connect(self, SIGNAL("linkClicked(const QUrl &)"), self.onWebLinkClicked)
        self.page().setLinkDelegationPolicy( QWebPage.DelegateAllLinks )
    def onWebLinkClicked(self, url):
        print "XXXclicked"
        QDesktopServices.openUrl(url)
