// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobView.h
//! @brief     Defines class JobView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBVIEW_H
#define JOBVIEW_H

#include "WinDllMacros.h"
#include "fancymainwindow.h"

struct JobViewPrivate;
class JobQueueModel;
class JobItem;
class ProjectManager;

namespace Manhattan {
    class ProgressBar;
}

//! Main class to represent list of jobs, show job results and run real time simulation
class BA_CORE_API_ JobView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:

    enum ESubWindows { JOB_LIST_DOCK, REAL_TIME_DOCK, NUMBER_OF_DOCKS };

    enum EActivities { JOB_VIEW_ACTIVITY, REAL_TIME_ACTIVITY };

    JobView(JobQueueModel *jobQueueModel, ProjectManager *projectManager, QWidget *parent = 0);
    virtual ~JobView();

    void setProgressBar(Manhattan::ProgressBar *progressBar);

signals:
    void focusRequest(int);
    void activityChanged(int activity);

public slots:
    void updateGlobalProgressBar(int);
    void onFocusRequest(JobItem *);
    void resetToDefaultLayout();
    void setActivity(int activity);

private:
    void initWindows();
    void connectSignals();

    JobViewPrivate *m_d;
};




#endif
