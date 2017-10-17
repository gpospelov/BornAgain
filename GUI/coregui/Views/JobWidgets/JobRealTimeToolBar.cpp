// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobRealTimeToolBar.cpp
//! @brief     Implements class JobRealTimeToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobRealTimeToolBar.h"
#include <QToolButton>

JobRealTimeToolBar::JobRealTimeToolBar(QWidget* parent)
    : StyledToolBar(parent)
    , m_resetParametersButton(new QToolButton)
{
    setMinimumSize(minimumHeight(), minimumHeight());

    m_resetParametersButton->setText("Reset values");
    m_resetParametersButton->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetParametersButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_resetParametersButton->setToolTip("Reset parameter tree to initial values");
    addWidget(m_resetParametersButton);

    connect(m_resetParametersButton, &QToolButton::clicked,
            this, &JobRealTimeToolBar::resetParameters);
}

