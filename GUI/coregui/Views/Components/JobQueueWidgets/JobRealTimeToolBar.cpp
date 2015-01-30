// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobRealTimeToolBar.cpp
//! @brief     Implements class JobRealTimeToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobRealTimeToolBar.h"
#include <QStyle>
#include <QToolButton>
#include <QLabel>

//! main tool bar on top of SampleView window
JobRealTimeToolBar::JobRealTimeToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_resetParametersButton(0)
    , m_exportParametersButton(0)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setMinimumSize(25, 25);

    setContentsMargins(0,0,0,0);

    // projections button
    m_resetParametersButton = new QToolButton;
    m_resetParametersButton->setText("Reset Values");
    m_resetParametersButton->setIcon(QIcon(":/images/toolbar_refresh.png"));
    m_resetParametersButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_resetParametersButton->setToolTip("Reset parameter tree to initial values");
    //m_importParametersButton->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(m_resetParametersButton, SIGNAL(clicked()), this, SIGNAL(resetParameters()));
    addWidget(m_resetParametersButton);

    // plot properties button
//    m_exportParametersButton = new QToolButton;
//    m_exportParametersButton->setText("Export Values");
//    m_exportParametersButton->setIcon(QIcon(":/images/toolbar_parameter_export.png"));
//    m_exportParametersButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    m_exportParametersButton->setToolTip("Propagate current parameter values \nback to the original model.");
//    connect(m_exportParametersButton, SIGNAL(clicked()), this, SIGNAL(exportParameters()));
//    addWidget(m_exportParametersButton);
}

