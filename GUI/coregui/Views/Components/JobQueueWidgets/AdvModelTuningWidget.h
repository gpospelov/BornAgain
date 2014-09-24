#ifndef ADVMODELTUNINGWIDGET_H
#define ADVMODELTUNINGWIDGET_H

#include <QWidget>
class QLabel;
class JobItem;
class QuickSimulationSettings;
class QTreeView;

class AdvModelTuningWidget : public QWidget
{
    Q_OBJECT

public:

    AdvModelTuningWidget(QWidget *parent = 0);
    virtual ~AdvModelTuningWidget() {}

    void setCurrentItem(JobItem *item);

private:
    JobItem *m_currentJobItem;
    QuickSimulationSettings *m_quickSimulationSettings;
    QTreeView *m_treeView;
};



#endif

