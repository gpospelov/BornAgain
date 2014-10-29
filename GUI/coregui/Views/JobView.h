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

    enum SubWindows
    {
        JobListDock,
        RealTimeDock,
        NumberOfDocks
    };

    enum Activities
    {
        JobViewActivity,
        RealTimeActivity
    };

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
