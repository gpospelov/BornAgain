//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobView.cpp
//! @brief     Implements class JobView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/JobView.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/CommonWidgets/DocksController.h"
#include "GUI/coregui/Views/FitWidgets/FitActivityPanel.h"
#include "GUI/coregui/Views/JobView.h"
#include "GUI/coregui/Views/JobWidgets/JobMessagePanel.h"
#include "GUI/coregui/Views/JobWidgets/JobOutputDataWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobProgressAssistant.h"
#include "GUI/coregui/Views/JobWidgets/JobRealTimeWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobSelectorWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobViewActivities.h"
#include "GUI/coregui/Views/JobWidgets/JobViewFlags.h"
#include "GUI/coregui/Views/JobWidgets/JobViewStatusBar.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QMenu>

JobView::JobView(MainWindow* mainWindow)
    : m_docks(new DocksController(this))
    , m_statusBar(new JobViewStatusBar(mainWindow))
    , m_progressAssistant(new JobProgressAssistant(mainWindow))
    , m_currentItem(nullptr)
    , m_mainWindow(mainWindow) {

    setObjectName("JobView");
    createSubWindows();
    connectSignals();
}

DocksController* JobView::docks() {
    return m_docks;
}

void JobView::addDockActionsToMenu(QMenu* menu) {
    m_docks->addDockActionsToMenu(menu);

    menu->addSeparator();

    QAction* action = new QAction(menu);
    action->setText("Reset to default layout");
    connect(action, &QAction::triggered, this, &JobView::resetLayout);
    menu->addAction(action);
}

void JobView::onFocusRequest(JobItem* jobItem) {
    if (jobItem->runInBackground())
        return;

    if (jobItem != m_jobSelector->currentJobItem()) {
        m_jobSelector->makeJobItemSelected(jobItem);
        setAppropriateActivityForJob(jobItem);
    }

    emit focusRequest(MainWindow::JOB);
}

//! Sets docks visibility in accordance with required activity.

void JobView::setActivity(int activity) {
    QVector<JobViewFlags::Dock> docksToShow =
        JobViewActivities::activeDocks(JobViewFlags::Activity(activity));

    std::vector<int> docks_id;
    for (auto x : docksToShow)
        docks_id.push_back(static_cast<int>(x));

    m_docks->setVisibleDocks(docks_id);
    emit activityChanged(activity);
}

//! Propagates change in JobItem's selection down into main widgets.

void JobView::onSelectionChanged(JobItem* jobItem) {
    m_jobOutputDataWidget->setItem(jobItem);
    m_jobRealTimeWidget->setItem(jobItem);
    m_fitActivityPanel->setItem(jobItem);
}

void JobView::showEvent(QShowEvent* event) {
    // #TODO refactor this after status bar is empty
    if (isVisible())
        m_statusBar->show();

    QMainWindow::showEvent(event);
}

void JobView::hideEvent(QHideEvent* event) {
    if (isHidden())
        m_statusBar->hide();

    QMainWindow::hideEvent(event);
}

void JobView::createSubWindows() {
    m_jobOutputDataWidget = new JobOutputDataWidget(m_mainWindow->jobModel(), this);
    m_jobSelector = new JobSelectorWidget(m_mainWindow->jobModel(), this);
    m_jobRealTimeWidget = new JobRealTimeWidget(m_mainWindow->jobModel(), this);
    m_fitActivityPanel = new FitActivityPanel(m_mainWindow->jobModel(), this);
    m_jobMessagePanel = new JobMessagePanel(this);

    m_docks->addWidget(JobViewFlags::JOB_LIST_DOCK, m_jobSelector, Qt::LeftDockWidgetArea);
    m_docks->addWidget(JobViewFlags::REAL_TIME_DOCK, m_jobRealTimeWidget, Qt::RightDockWidgetArea);
    m_docks->addWidget(JobViewFlags::FIT_PANEL_DOCK, m_fitActivityPanel, Qt::RightDockWidgetArea);
    m_docks->addWidget(JobViewFlags::JOB_MESSAGE_DOCK, m_jobMessagePanel, Qt::BottomDockWidgetArea);

    connect(m_jobMessagePanel, &JobMessagePanel::widgetHeightRequest, m_docks,
            &DocksController::setDockHeightForWidget);

    m_fitActivityPanel->setRealTimeWidget(m_jobRealTimeWidget);
    m_fitActivityPanel->setJobMessagePanel(m_jobMessagePanel);

    setCentralWidget(m_jobOutputDataWidget);

    resetLayout();
}

void JobView::connectSignals() {
    connectActivityRelated();
    connectJobRelated();
}

//! Connects signal related to activity change.

void JobView::connectActivityRelated() {
    // Change activity requests: JobViewStatusBar -> this
    connect(m_statusBar, &JobViewStatusBar::changeActivityRequest, this, &JobView::setActivity);

    // Activity was changed: this -> JobViewStatusBar
    connect(this, &JobView::activityChanged, m_statusBar, &JobViewStatusBar::onActivityChanged);

    // Activity was changed: this -> JobOutputDataWidget
    connect(this, &JobView::activityChanged, m_jobOutputDataWidget,
            &JobOutputDataWidget::onActivityChanged);
}

//! Connects signals related to JobItem

void JobView::connectJobRelated() {
    // Focus request: JobModel -> this
    connect(m_mainWindow->jobModel(), &JobModel::focusRequest, this, &JobView::onFocusRequest);

    // JobItem selection: JobSelectorWidget -> this
    connect(m_jobSelector, &JobSelectorWidget::selectionChanged, this,
            &JobView::onSelectionChanged);
}

//! Sets appropriate activity for new JobItem

void JobView::setAppropriateActivityForJob(JobItem* jobItem) {
    if (!jobItem)
        return;

    if (jobItem->isValidForFitting())
        setActivity(JobViewFlags::FITTING_ACTIVITY);
}

void JobView::resetLayout() {
    m_docks->resetLayout();
    setActivity(static_cast<int>(JobViewFlags::JOB_VIEW_ACTIVITY));
}
