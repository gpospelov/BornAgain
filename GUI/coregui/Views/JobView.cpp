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
#include "GUI/coregui/Views/JobWidgets/JobOutputDataWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobProgressAssistant.h"
#include "GUI/coregui/Views/JobWidgets/JobSelectorWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobViewDocks.h"
#include "GUI/coregui/Views/JobWidgets/JobViewFlags.h"
#include "GUI/coregui/Views/JobWidgets/JobViewStatusBar.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QMenu>

JobView::JobView(MainWindow* mainWindow)
    : m_docks(new JobViewDocks(this))
    , m_statusBar(new JobViewStatusBar(mainWindow))
    , m_progressAssistant(new JobProgressAssistant(mainWindow))
    , m_currentItem(nullptr)
    , m_mainWindow(mainWindow) {
    setObjectName("JobView");
    m_docks->initViews(mainWindow->jobModel());

    connectSignals();
}

DocksController* JobView::docks() {
    return m_docks;
}

void JobView::onFocusRequest(JobItem* jobItem) {
    if (jobItem->runInBackground())
        return;

    if (jobItem != m_docks->jobSelector()->currentJobItem()) {
        m_docks->jobSelector()->makeJobItemSelected(jobItem);
        setAppropriateActivityForJob(jobItem);
    }

    emit focusRequest(MainWindow::JOB);
}

//! Sets docks visibility in accordance with required activity.

void JobView::setActivity(int activity) {
    m_docks->setActivity(activity);
    emit activityChanged(activity);
}

//! Propagates change in JobItem's selection down into main widgets.

void JobView::onSelectionChanged(JobItem* jobItem) {
    m_docks->setItem(jobItem);
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
    connect(this, &JobView::activityChanged, m_docks->jobOutputDataWidget(),
            &JobOutputDataWidget::onActivityChanged);
}

//! Connects signals related to JobItem

void JobView::connectJobRelated() {
    // Focus request: JobModel -> this
    connect(m_mainWindow->jobModel(), &JobModel::focusRequest, this, &JobView::onFocusRequest);

    // JobItem selection: JobSelectorWidget -> this
    connect(m_docks->jobSelector(), &JobSelectorWidget::selectionChanged, this,
            &JobView::onSelectionChanged);
}

//! Sets appropriate activity for new JobItem

void JobView::setAppropriateActivityForJob(JobItem* jobItem) {
    if (!jobItem)
        return;

    if (jobItem->isValidForFitting())
        setActivity(JobViewFlags::FITTING_ACTIVITY);
}
