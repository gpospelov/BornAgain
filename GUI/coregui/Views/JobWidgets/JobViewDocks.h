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

#ifndef JOBVIEWDOCKS_H
#define JOBVIEWDOCKS_H

#include "WinDllMacros.h"
#include <QObject>
#include <QVector>

class QDockWidget;
class JobView;

//! The JobViewDocks class assists JobView in holding all main job widgets and corresponding
//! dock containers.
//! Provides Job Activities switch logic for all of (JobSelectorWidget, JobOutputDataWidget,
//! JobRealTimeWidget and FitPanelWidget).

class JobViewDocks : public QObject {
    Q_OBJECT

public:

    enum EDocksId {
        JOB_LIST_DOCK,
        REAL_TIME_DOCK,
        FIT_PANEL_DOCK,
        JOB_MESSAGE_DOCK,
        NUMBER_OF_DOCKS
    };

    JobViewDocks(JobView *parent = 0);

    void initViews(class JobModel *jobModel);

    QWidget *jobWidget(EDocksId dockId);
    QDockWidget *dock(EDocksId dockId);
    QWidget *centralWidget();


    class JobRealTimeWidget *jobRealTimeWidget() { return m_jobRealTimeWidget;}
    class FitActivityPanel *fitActivityPanel() { return m_fitActivityPanel; }
    class JobSelectorWidget *jobSelector() { return m_jobSelector; }
    class JobOutputDataWidget *jobOutputDataWidget() { return m_jobOutputDataWidget; }

private:
    void initJobWidgets(class JobModel *jobModel);
    void initDocks();

    class JobSelectorWidget *m_jobSelector;
    class JobOutputDataWidget *m_jobOutputDataWidget;
    class JobRealTimeWidget *m_jobRealTimeWidget;
    class FitActivityPanel *m_fitActivityPanel;

    QVector<QWidget *> m_jobWidgets;
    QVector<QDockWidget *> m_dockWidgets;

    JobView *m_jobView;
};

#endif

