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

//! main tool bar on top of SampleView window
JobRealTimeToolBar::JobRealTimeToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_resetParametersButton(0)
{
    m_resetParametersButton = new QToolButton;
    m_resetParametersButton->setText("Reset Values");
    m_resetParametersButton->setIcon(QIcon(":/images/toolbar_refresh.png"));
    m_resetParametersButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_resetParametersButton->setToolTip("Reset parameter tree to initial values");
    connect(m_resetParametersButton, SIGNAL(clicked()), this, SIGNAL(resetParameters()));
    addWidget(m_resetParametersButton);
}

