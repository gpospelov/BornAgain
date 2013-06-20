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

    m_materialBrowserAction = new QAction(QIcon(":/SampleDesigner/images/document-attribute-m.png"), tr("Material Editor (M)"), this);
    m_materialBrowserAction->setShortcut(Qt::Key_M);
    connect(m_materialBrowserAction, SIGNAL(triggered()), this, SLOT(materialBrowserCall()));
    addAction(m_materialBrowserAction);

    m_zoomOutAction = new QAction(QIcon(":/SampleDesigner/images/magnifier-zoom-out.png"), tr("Zoom out, Ctrl-"), this);
    m_zoomOutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    connect(m_zoomOutAction, SIGNAL(triggered()), this, SIGNAL(zoomOut()));
    addAction(m_zoomOutAction);

    m_zoomInAction = new QAction(QIcon(":/SampleDesigner/images/magnifier-zoom-in.png"), tr("Zoom in, Ctrl+"), this);
    m_zoomInAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
    connect(m_zoomInAction, SIGNAL(triggered()), this, SIGNAL(zoomIn()));
    addAction(m_zoomInAction);

    m_zoomFitAction = new QAction(QIcon(":/SampleDesigner/images/magnifier-zoom-fit.png"), tr("Zoom fit"), this);
    connect(m_zoomFitAction, SIGNAL(triggered()), this, SIGNAL(zoomFit()));
    addAction(m_zoomFitAction);

}


void SampleToolBar::materialBrowserCall()
{
    std::cout << "SampleToolBar::materialBrowserCall() ->" << std::endl;
    MaterialBrowser::BrowserViewCall();
}
