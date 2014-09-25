#ifndef ADVMODELTUNINGWIDGET_H
#define ADVMODELTUNINGWIDGET_H

#include "ItemLink.h"
#include <QWidget>

class JobItem;
class QuickSimulationSettings;
class ModelTuningDelegate;
class JobQueueData;
class QTreeView;
class QStandardItemModel;


class AdvModelTuningWidget : public QWidget
{
    Q_OBJECT

public:

    AdvModelTuningWidget(JobQueueData *jobQueueData, QWidget *parent = 0);
    virtual ~AdvModelTuningWidget();

    void setCurrentItem(JobItem *item);

public slots:
    void onCurrentLinkChanged(ItemLink link);
    void onSliderValueChanged(double value);

private:
    void updateParameterModel();

    JobQueueData *m_jobQueueData;
    JobItem *m_currentJobItem;
    QuickSimulationSettings *m_quickSimulationSettings;
    QTreeView *m_treeView;
    QStandardItemModel *m_parameterModel;
    ModelTuningDelegate *m_delegate;
};



#endif

