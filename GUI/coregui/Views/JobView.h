#ifndef JOBVIEW_H
#define JOBVIEW_H

#include "WinDllMacros.h"
#include "fancymainwindow.h"

struct JobViewPrivate;
class JobQueueModel;
class JobItem;

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

    JobView(JobQueueModel *jobQueueModel, QWidget *parent = 0);
    virtual ~JobView();

    void setProgressBar(Manhattan::ProgressBar *progressBar);

signals:
    void focusRequest(int);

public slots:
    void updateGlobalProgressBar(int);
    void onFocusRequest(JobItem *);
    void resetToDefaultLayout();
    void onJobViewActivityRequest();
    void onRealTimeActivityRequest();

private:
    void initWindows();
    void connectSignals();

    JobViewPrivate *m_d;
};




#endif
