#ifndef ADVMODELTUNINGWIDGET_H
#define ADVMODELTUNINGWIDGET_H

#include <QWidget>
class QLabel;
class JobItem;

class AdvModelTuningWidget : public QWidget
{
    Q_OBJECT

public:

    AdvModelTuningWidget(QWidget *parent = 0);
    virtual ~AdvModelTuningWidget() {}

    void setCurrentItem(JobItem *item);

private:
    QLabel *m_label;
    JobItem *m_currentJobItem;
};



#endif

