// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorToolBar.cpp
//! @brief     Implements class JobSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobSelectorToolBar.h"
#include "JobSelectorActions.h"
#include <QToolButton>

JobSelectorToolBar::JobSelectorToolBar(JobSelectorActions* actions, QWidget* parent)
    : StyledToolBar(parent)
    , m_runJobButton(new QToolButton)
    , m_removeJobButton(new QToolButton)
{
    m_runJobButton->setText(QStringLiteral("Run"));
    m_runJobButton->setIcon(QIcon(":/images/toolbar16light_run.svg"));
    m_runJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_runJobButton->setToolTip("Run currently selected job");
    addWidget(m_runJobButton);

    m_removeJobButton->setText("Remove");
    m_removeJobButton->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeJobButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeJobButton->setToolTip("Remove currently selected job.");
    addWidget(m_removeJobButton);

    connect(m_runJobButton, &QToolButton::clicked, actions, &JobSelectorActions::onRunJob);
    connect(m_removeJobButton, &QToolButton::clicked, actions, &JobSelectorActions::onRemoveJob);
}
