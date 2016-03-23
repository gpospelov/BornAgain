// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/OutputDataToolBar.cpp
//! @brief     Implements class OutputDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "OutputDataToolBar.h"
#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <QLabel>
#include <iostream>

#include "styledbar.h"

//! main tool bar on top of SampleView window
OutputDataToolBar::OutputDataToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_togglePropertyPanelButton(0)
    , m_toggleProjectionsButton(0)
    , m_resetViewButton(0)
    , m_savePlotButton(0)


{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setContentsMargins(0,0,0,0);

    // plot properties button
    m_togglePropertyPanelButton = new QToolButton;
    m_togglePropertyPanelButton->setText("Plot Properties");
    m_togglePropertyPanelButton->setIcon(QIcon(":/images/toolbar_propertypanel.png"));
    m_togglePropertyPanelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_togglePropertyPanelButton->setToolTip("Toggle Property Panel, Ctrl+P");
    m_togglePropertyPanelButton->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(m_togglePropertyPanelButton, SIGNAL(clicked()), this, SIGNAL(togglePropertyPanel()));
    addWidget(m_togglePropertyPanelButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    // projections button
    m_toggleProjectionsButton = new QToolButton;
    m_toggleProjectionsButton->setText("Projections");
    m_toggleProjectionsButton->setIcon(QIcon(":/images/toolbar_projections.png"));
    m_toggleProjectionsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toggleProjectionsButton->setToolTip("Toggle Projections, Ctrl+O");
    m_toggleProjectionsButton->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(m_toggleProjectionsButton, SIGNAL(clicked()), this, SIGNAL(toggleProjections()));
    addWidget(m_toggleProjectionsButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    // reset view button
    m_resetViewButton = new QToolButton;
    m_resetViewButton->setText("Reset View");
    m_resetViewButton->setIcon(QIcon(":/images/toolbar_refresh.png"));
    m_resetViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_resetViewButton->setToolTip("TReset View, Ctrl+R");
    m_resetViewButton->setShortcut(Qt::CTRL + Qt::Key_R);
    connect(m_resetViewButton, SIGNAL(clicked()), this, SIGNAL(resetView()));
    addWidget(m_resetViewButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    // save plot button
    m_savePlotButton = new QToolButton;
    m_savePlotButton->setText("Save Plot");
    m_savePlotButton->setIcon(QIcon(":/images/toolbar_save.png"));
    m_savePlotButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_savePlotButton->setToolTip("Save Plot, Ctrl+S");
    m_savePlotButton->setShortcut(Qt::CTRL + Qt::Key_S);
    connect(m_savePlotButton, SIGNAL(clicked()), this, SIGNAL(savePlot()));
    addWidget(m_savePlotButton);

    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}
