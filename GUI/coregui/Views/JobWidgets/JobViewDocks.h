// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewDocks.h
//! @brief     Declares class JobViewDocks
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

#include <QObject>
#include <QVector>
#include "JobViewFlags.h"
#include "WinDllMacros.h"

class QDockWidget;
class JobView;
class JobSelectorWidget;
class JobOutputDataWidget;
class JobRealTimeWidget;
class FitActivityPanel;
class JobMessagePanel;


//! The JobViewDocks class assists JobView in holding all main job widgets and corresponding
//! dock containers.

//! It's main method setActivity handles visibility logic for all of (JobSelectorWidget,
//! JobOutputDataWidget, JobRealTimeWidget and FitPanelWidget).

class BA_CORE_API_ JobViewDocks : public QObject {
    Q_OBJECT

public:
    JobViewDocks(JobView *parent = 0);

    void initViews(class JobModel *jobModel);

    class JobRealTimeWidget *jobRealTimeWidget() { return m_jobRealTimeWidget;}
    class FitActivityPanel *fitActivityPanel() { return m_fitActivityPanel; }
    class JobSelectorWidget *jobSelector() { return m_jobSelector; }
    class JobOutputDataWidget *jobOutputDataWidget() { return m_jobOutputDataWidget; }
    class JobMessagePanel *jobMessagePanel() { return m_jobMessagePanel; }

    void setActivity(int activity);
    void setItem(class JobItem *jobItem);

public slots:
    void onResetLayout();
    void onToggleJobSelector();
    void setDockHeightForWidget(int height);
    void onWidgetCloseRequest();
    void dockToMinMaxSizes();

private:
    //! Stores sizes of dock widget
    struct DockSizeInfo {
        DockSizeInfo():m_dock(0){}
        QDockWidget *m_dock;
        QSize m_min_size;
        QSize m_max_size;
    };

    QWidget *jobWidget(JobViewFlags::Dock dockId);
    QDockWidget *dock(JobViewFlags::Dock dockId);
    QWidget *centralWidget();
    void initJobWidgets(class JobModel *jobModel);
    void initDocks();
    QDockWidget *findDock(QWidget *widget);

    JobSelectorWidget *m_jobSelector;
    JobOutputDataWidget *m_jobOutputDataWidget;
    JobRealTimeWidget *m_jobRealTimeWidget;
    FitActivityPanel *m_fitActivityPanel;
    JobMessagePanel *m_jobMessagePanel;

    QVector<QWidget *> m_jobWidgets;
    QVector<QDockWidget *> m_dockWidgets;

    JobView *m_jobView;
    DockSizeInfo m_dock_info;

};

#endif // JOBVIEWDOCKS_H
