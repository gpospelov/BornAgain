#include "SampleToolBar.h"
#include "MaterialBrowser.h"
#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <iostream>


//! main tool bar on top of SampleView window
SampleToolBar::SampleToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    //m_materialBrowserAction = new QAction(QIcon(":/SampleDesigner/images/next.png"), tr("Material Editor"), this);
    m_materialBrowserAction = new QAction(QIcon(":/SampleDesigner/images/document-attribute-m.png"), tr("Material Editor"), this);
    addAction(m_materialBrowserAction);
    connect(m_materialBrowserAction, SIGNAL(triggered()), this, SLOT(materialBrowserCall()));

//    m_zoomInAction = new QAction(QIcon(":/SampleDesigner/images/next.png"), tr("Zoom in"), this);
    m_zoomInAction = new QAction(QIcon(":/SampleDesigner/images/magnifier-zoom-out.png"), tr("Zoom out"), this);



    addAction(m_zoomInAction);
//    addAction(m_zoomOutAction);
}


void SampleToolBar::materialBrowserCall()
{
    std::cout << "SampleToolBar::materialBrowserCall() ->" << std::endl;
    MaterialBrowser::BrowserViewCall();
}
