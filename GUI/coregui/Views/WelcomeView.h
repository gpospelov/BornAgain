#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWebView>

class WelcomeView : public QWebView
{
    Q_OBJECT

public:
    WelcomeView(QWidget *parent = 0);

public slots:
    void onWebLinkClicked(const QUrl &url);
};

#endif // WELCOMEVIEW_H
