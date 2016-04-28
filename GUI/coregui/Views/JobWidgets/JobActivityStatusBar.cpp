// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobActivityStatusBar.cpp
//! @brief     Implements class JobActivityStatusBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobActivityStatusBar.h"
#include "JobView.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QComboBox>

JobActivityStatusBar::JobActivityStatusBar(QWidget *parent)
    : QWidget(parent)
    , m_toggleJobListButton(0)
    , m_activityCombo(0)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    m_toggleJobListButton = new QToolButton;
    m_toggleJobListButton->setText("Job List");
    m_toggleJobListButton->setIcon(QIcon(":/images/toolbar_projections.png"));
    m_toggleJobListButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toggleJobListButton->setToolTip("Toggle job list view");
    connect(m_toggleJobListButton, SIGNAL(clicked()),
            this, SIGNAL(toggleJobListRequest()));

    m_activityCombo = new QComboBox();
    m_activityCombo->setToolTip("Main Activity Selector");
    m_activityCombo->addItems(JobView::getActivityStringList());
    connect(m_activityCombo, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(changeActivityRequest(int)));

    layout->addWidget(m_toggleJobListButton);
    layout->addWidget(m_activityCombo);

    setLayout(layout);

}

void JobActivityStatusBar::onActivityChanged(int activity)
{
    disconnect(m_activityCombo, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(changeActivityRequest(int)));

    m_activityCombo->setCurrentIndex(activity);

    connect(m_activityCombo, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(changeActivityRequest(int)));
}
