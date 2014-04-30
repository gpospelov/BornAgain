#include "OutputDataToolBar.h"
#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <iostream>

#include "styledbar.h"

//! main tool bar on top of SampleView window
OutputDataToolBar::OutputDataToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setContentsMargins(0,0,0,0);

    //m_togglePropertyPanelAction = new QAction(QIcon(":/OutputDataWidgets/images/next.png"), tr("Toogle Property Panel (P)"), this);
    m_togglePropertyPanelAction = new QAction(QIcon(":/SampleDesigner/images/next.png"), tr("Toogle Property Panel (P)"), this);
    m_togglePropertyPanelAction->setShortcut(Qt::Key_P);
    connect(m_togglePropertyPanelAction, SIGNAL(triggered()), this, SIGNAL(togglePropertyPanel()));
    addAction(m_togglePropertyPanelAction);

    addWidget(new Manhattan::StyledSeparator());

    //m_savePlotAction = new QAction(QIcon(":/OutputDataWidgets/images/filesave.png"), tr("Save, Ctrl+S"), this);
    m_savePlotAction = new QAction(QIcon(":/SampleDesigner/images/card--plus.png"), tr("Save, Ctrl+S"), this);
    m_savePlotAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    connect(m_savePlotAction, SIGNAL(triggered()), this, SIGNAL(savePlot()));
    addAction(m_savePlotAction);






//    insertSeparator(m_clearAllAction);
//    Manhattan::StyledSeparator *sep = new Manhattan::StyledSeparator(this);
//    addWidget(new Manhattan::StyledSeparator());


}
