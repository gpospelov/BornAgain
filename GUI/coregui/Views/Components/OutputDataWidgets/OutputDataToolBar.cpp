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


    m_togglePropertyPanelAction = new QAction(QIcon(":/SampleDesigner/images/sidebar.png"), tr("Toogle Property Panel, Ctrl+P"), this);
    m_togglePropertyPanelAction->setShortcut(Qt::CTRL + Qt::Key_P);
    this->connect(m_togglePropertyPanelAction, SIGNAL(triggered()), this, SIGNAL(togglePropertyPanel()));
    this->addAction(m_togglePropertyPanelAction);

    m_toggleProjectionsAction = new QAction(QIcon(":/SampleDesigner/images/application-resize-full.png"), tr("Toogle Projections, Ctrl+O"), this);
    m_toggleProjectionsAction->setShortcut(Qt::CTRL + Qt::Key_O);
    this->connect(m_toggleProjectionsAction, SIGNAL(triggered()), this, SIGNAL(toggleProjections()));
    this->addAction(m_toggleProjectionsAction);

    //this->addWidget(new Manhattan::StyledSeparator());

    m_resetViewAction = new QAction(QIcon(":/SampleDesigner/images/refresh.png"), tr("Reset View, Ctrl+R"), this);
    m_resetViewAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    this->connect(m_resetViewAction, SIGNAL(triggered()), this, SIGNAL(resetView()));
    this->addAction(m_resetViewAction);

    m_savePlotAction = new QAction(QIcon(":/SampleDesigner/images/filesave.png"), tr("Save, Ctrl+S"), this);
    m_savePlotAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    this->connect(m_savePlotAction, SIGNAL(triggered()), this, SIGNAL(savePlot()));
    this->addAction(m_savePlotAction);


//    insertSeparator(m_clearAllAction);
//    Manhattan::StyledSeparator *sep = new Manhattan::StyledSeparator(this);
//    addWidget(new Manhattan::StyledSeparator());


}
