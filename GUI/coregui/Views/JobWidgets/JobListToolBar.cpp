// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobListToolBar.cpp
//! @brief     Implements class JobListToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobListToolBar.h"
#include <QStyle>
#include <QToolButton>
#include <QLabel>

JobListToolBar::JobListToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_runJobButton(0)
    , m_removeJobButton(0)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setMinimumSize(25, 25);

    setContentsMargins(0,0,0,0);

    // projections button
    m_runJobButton = new QToolButton;
    m_runJobButton->setText("Run Job");
    m_runJobButton->setIcon(QIcon(":/images/main_simulation.png"));
    m_runJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_runJobButton->setToolTip("Run currently selected job");
    connect(m_runJobButton, SIGNAL(clicked()), this, SIGNAL(runJob()));
    addWidget(m_runJobButton);

    // plot properties button
    m_removeJobButton = new QToolButton;
    m_removeJobButton->setText("Remove Job");
    m_removeJobButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_removeJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeJobButton->setToolTip("Remove currently selected job.");
    connect(m_removeJobButton, SIGNAL(clicked()), this, SIGNAL(removeJob()));
    addWidget(m_removeJobButton);
}

