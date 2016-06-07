// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobViewDocks.h
//! @brief     Implements class JobViewDocks
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobViewDocks.h"
#include "JobView.h"
#include "JobModel.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include "JobRealTimeWidget.h"
#include "FitActivityPanel.h"
#include "JobMessagePanel.h"
#include <QAbstractItemView>

JobViewDocks::JobViewDocks(JobView *parent)
    : QObject(parent)
    , m_jobSelector(0)
    , m_jobOutputDataWidget(0)
    , m_jobRealTimeWidget(0)
    , m_fitActivityPanel(0)
    , m_jobView(parent)
{

}


//! Returns job widget with given Id.

QWidget *JobViewDocks::jobWidget(JobViewDocks::EDocksId dockId)
{
    Q_ASSERT(dockId >=0 && dockId<m_jobWidgets.size());
    return m_jobWidgets[dockId];
}

//! Returns dock with given id.

QDockWidget *JobViewDocks::dock(JobViewDocks::EDocksId dockId)
{
    Q_ASSERT(dockId >=0 && dockId<m_dockWidgets.size());
    return m_dockWidgets[dockId];
}

QWidget *JobViewDocks::centralWidget()
{
    return m_jobOutputDataWidget;
}

//! Inits all main JobWidgets.

void JobViewDocks::initJobWidgets(JobModel *jobModel)
{
    m_jobWidgets.resize(NUMBER_OF_DOCKS);
    m_dockWidgets.resize(NUMBER_OF_DOCKS);

    m_jobOutputDataWidget = new JobOutputDataWidget(jobModel, m_jobView);

    m_jobSelector = new JobSelectorWidget(jobModel, m_jobView);
    m_jobWidgets[JOB_LIST_DOCK] = m_jobSelector;

    m_jobRealTimeWidget = new JobRealTimeWidget(jobModel, m_jobView);
    m_jobWidgets[REAL_TIME_DOCK] = m_jobRealTimeWidget;

    m_fitActivityPanel = new FitActivityPanel(jobModel, m_jobView);
    m_fitActivityPanel->setRealTimeWidget(m_jobRealTimeWidget);
    m_jobWidgets[FIT_PANEL_DOCK] = m_fitActivityPanel;

    m_jobWidgets[JOB_MESSAGE_DOCK] = new JobMessagePanel(m_jobView);

    m_jobView->setCentralWidget(centralWidget());
}

//! Init docks for JobView

void JobViewDocks::initDocks()
{
    for (int i = 0; i < NUMBER_OF_DOCKS; i++) {
        QWidget *subWindow = jobWidget(EDocksId(i));
        m_dockWidgets[i] = m_jobView->addDockForWidget(subWindow);

        // Since we have 1-pixel splitters, we generally want to remove
        // frames around item views. So we apply this hack for now.
        QList<QAbstractItemView*> frames =
                subWindow->findChildren<QAbstractItemView*>();
        for (int i = 0 ; i< frames.count(); ++i)
            frames[i]->setFrameStyle(QFrame::NoFrame);

    }

    m_jobView->resetToDefaultLayout();
}
