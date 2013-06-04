#ifndef MATERIALBROWSER_H
#define MATERIALBROWSER_H

#include <QObject>

class QWidget;
class MaterialBrowserView;
class MaterialBrowserModel;


//! main class to access materials
class MaterialBrowser : public QObject
{
    Q_OBJECT
public:
    MaterialBrowser(QWidget *parent = 0);
    virtual ~MaterialBrowser();

    static MaterialBrowser *instance();

public slots:
    //! create new MaterialBrowserView or raise old one if exists
    void BrowserViewCall();

    //! delete MaterialBrowserView if it was closed by the user
    void BrowserViewOnCloseEvent();

private:
    QWidget *m_parent;
    static MaterialBrowser *m_instance;
    MaterialBrowserView *m_browserView;
    MaterialBrowserModel *m_browserModel;
};

#endif // MATERIALBROWSER_H
