#include "SampleToolBar.h"
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
    m_goBackAction = new QAction(QIcon(":/SampleDesigner/images/next.png"), tr("Material Editor"), this);
   connect(m_goBackAction, SIGNAL(triggered()), this, SLOT(materialEditorCall()));

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    addAction(m_goBackAction);
}


void SampleToolBar::materialEditorCall()
{
    std::cout << "SampleView::materialEditorCall() ->" << std::endl;
}
