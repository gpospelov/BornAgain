#ifndef MATERIALBROWSER_H
#define MATERIALBROWSER_H

#include "MaterialProperty.h"

#include <QObject>
#include <QColor>
#include <QIcon>
#include <QPixmap>

class QWidget;
class MaterialBrowserView;
class MaterialBrowserModel;


//! The MaterialBrowser is the main class to create, edit and access materials.
//! MaterialBrowser is created/deleted in SampleView, used by others via instance() method.
class MaterialBrowser : public QObject
{
    Q_OBJECT
public:
    MaterialBrowser(QWidget *parent = 0);
    virtual ~MaterialBrowser();

    static MaterialBrowser *instance();

    static MaterialProperty getMaterialProperty() { return instance()->this_getSelectedMaterialProperty(); }

public slots:
    //! create new MaterialBrowserView or raise old one if exists
    //! @param isModal The dialog window will be independent from main view, if true
    void BrowserViewCall(bool isModal = true);

    //! delete MaterialBrowserView if it was closed by the user
    void BrowserViewOnCloseEvent();

private:
    MaterialProperty this_getSelectedMaterialProperty();

    QWidget *m_parent;
    static MaterialBrowser *m_instance;
    MaterialBrowserView *m_browserView;
    MaterialBrowserModel *m_browserModel;
};

#endif // MATERIALBROWSER_H
