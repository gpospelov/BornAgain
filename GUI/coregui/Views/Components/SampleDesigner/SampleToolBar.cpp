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
    m_materialBrowserAction = new QAction(QIcon(":/SampleDesigner/images/next.png"), tr("Material Editor"), this);

    connect(m_materialBrowserAction, SIGNAL(triggered()), this, SLOT(materialBrowserCall()));

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    addAction(m_materialBrowserAction);
}


void SampleToolBar::materialBrowserCall()
{
    std::cout << "SampleToolBar::materialBrowserCall() ->" << std::endl;
    MaterialBrowser::BrowserViewCall();
}
