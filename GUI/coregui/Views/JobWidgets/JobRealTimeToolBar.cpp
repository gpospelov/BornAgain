// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobRealTimeToolBar.cpp
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

    m_resetParametersButton = new QToolButton;
    m_resetParametersButton->setText("Reset Values");
    m_resetParametersButton->setIcon(QIcon(":/images/toolbar_refresh.png"));
    m_resetParametersButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_resetParametersButton->setToolTip("Reset parameter tree to initial values");
    connect(m_resetParametersButton, SIGNAL(clicked()), this, SIGNAL(resetParameters()));
    addWidget(m_resetParametersButton);
}

