// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobActivityStatusBar.cpp
//! @brief     Implements class JobActivityStatusBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "JobActivityStatusBar.h"
#include "JobViewActivities.h"
#include "mainwindow.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QToolButton>

JobActivityStatusBar::JobActivityStatusBar(MainWindow* mainWindow)
    : QWidget(mainWindow), m_toggleJobListButton(nullptr)
    , m_activityCombo(nullptr), m_dockMenuButton(nullptr)
    , m_mainWindow(mainWindow)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    m_toggleJobListButton = new QToolButton;
    m_toggleJobListButton->setText("Job List");
    m_toggleJobListButton->setIcon(QIcon(":/images/statusbar_joblist.svg"));
    m_toggleJobListButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toggleJobListButton->setToolTip("Toggle job list view");
    connect(m_toggleJobListButton, &QToolButton::clicked,
            this, &JobActivityStatusBar::toggleJobSelectorRequest);

    m_activityCombo = new QComboBox();
    m_activityCombo->setToolTip("Main Activity Selector");
    m_activityCombo->addItems(JobViewActivities::activityList());
    connect(m_activityCombo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &JobActivityStatusBar::changeActivityRequest);

    m_dockMenuButton = new QToolButton;
    m_dockMenuButton->setIcon(QIcon(":/images/statusbar_dockmenu.svg"));
    m_dockMenuButton->setToolTip("Docks layout menu");
    connect(m_dockMenuButton, &QToolButton::clicked,
            this, &JobActivityStatusBar::dockMenuRequest);

    layout->addWidget(m_toggleJobListButton);
    layout->addStretch();
    layout->addWidget(m_activityCombo);
    layout->addWidget(m_dockMenuButton);

    setLayout(layout);
    initAppearance();
}

void JobActivityStatusBar::onActivityChanged(int activity)
{
    disconnect(m_activityCombo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &JobActivityStatusBar::changeActivityRequest);

    m_activityCombo->setCurrentIndex(activity);

    connect(m_activityCombo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &JobActivityStatusBar::changeActivityRequest);
}

//! Init appearance of MainWindow's statusBar.

void JobActivityStatusBar::initAppearance()
{
    Q_ASSERT(m_mainWindow);
    m_mainWindow->statusBar()->addWidget(this, 1);
    m_mainWindow->statusBar()->setSizeGripEnabled(false);
    this->hide();
}
