#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QMap>

class OutputDataWidget;
class JobQueueModel;
class QStackedWidget;
class QModelIndex;
class JobItem;
class JobOutputDataToolBar;


class BA_CORE_API_ JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobOutputDataWidget(JobQueueModel *jobQueueModel, QWidget *parent = 0);

    void setJobQueueModel(JobQueueModel *jobQueueModel);

    JobOutputDataToolBar *getToolBar() { return m_toolBar; }

signals:
    void jobViewActivityRequest(int activity);

public slots:
    void itemClicked(JobItem *item);
    void onJobItemDelete(JobItem *item);
    void onJobItemFinished(const QString &identifier);
    void togglePropertyPanel();
    void toggleProjections();
    void resetTriggered();
    void savePlot();
    void onActivityChanged(int);

private:
    void connectSignals();
    OutputDataWidget *getCurrentOutputDataWidget();

    JobQueueModel *m_jobQueueModel;
    JobItem *m_currentJobItem;
    QStackedWidget *m_stack;
    QMap<JobItem *, OutputDataWidget *> m_jobItemToPlotWidget;
    JobOutputDataToolBar *m_toolBar;
};


#endif
