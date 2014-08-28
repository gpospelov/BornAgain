#ifndef JOBQUEUEVIEW_H
#define JOBQUEUEVIEW_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QVector>

class JobSelectorWidget;
class JobOutputDataWidget;

class QListView;
class QPushButton;
class JobQueueModel;
class QDockWidget;
class QSplitter;
class JobItem;

namespace Manhattan {
    class ProgressBar;
}


class BA_CORE_API_ JobQueueView : public QWidget
{
    Q_OBJECT

public:
    enum SubWindows
    {
        JobSelectorWindow,
        JobPropertiesWindow,
        JobOutputDataWindow,
        NumberOfSubWindows
    };

    JobQueueView(JobQueueModel *model, QWidget *parent = 0);
    virtual ~JobQueueView() {}

    void setProgressBar(Manhattan::ProgressBar *progressBar);

signals:
    void focusRequest(int);

public slots:
    void updateGlobalProgressBar(int);
    void onFocusRequest(JobItem *);

private:
    JobQueueModel *m_jobQueueModel;
    QSplitter *m_splitter;
    JobSelectorWidget *m_jobSelector;
    JobOutputDataWidget *m_jobOutputData;
    Manhattan::ProgressBar *m_progressBar; //!< general progress bar
};

#endif // JOBQUEUEVIEW_H
