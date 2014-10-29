#ifndef MODELTUNINGWIDGET_H
#define MODELTUNINGWIDGET_H

#include "ItemLink.h"
#include <QWidget>

class JobItem;
class SliderSettingsWidget;
class ModelTuningDelegate;
class JobQueueData;
class QTreeView;
class QStandardItemModel;
class SampleModel;
class InstrumentModel;


class ModelTuningWidget : public QWidget
{
    Q_OBJECT

public:

    ModelTuningWidget(JobQueueData *jobQueueData, QWidget *parent = 0);
    virtual ~ModelTuningWidget();

    void setCurrentItem(JobItem *item);

public slots:
    void onCurrentLinkChanged(ItemLink link);
    void onSliderValueChanged(double value);
    void restoreModelsOfCurrentJobItem();

private:
    void updateParameterModel();
    void backupModels();

    JobQueueData *m_jobQueueData;
    JobItem *m_currentJobItem;
    SliderSettingsWidget *m_sliderSettingsWidget;
    QTreeView *m_treeView;
    QStandardItemModel *m_parameterModel;
    ModelTuningDelegate *m_delegate;
    SampleModel *m_sampleModelBackup;
    InstrumentModel *m_instrumentModelBackup;
};



#endif

