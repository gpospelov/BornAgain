#ifndef DISTRIBUTIONPLOTWIDGET_H_
#define DISTRIBUTIONPLOTWIDGET_H_


#include "qcustomplot.h"
#include "DistributionItem.h"

class ParameterizedItem;
class AwesomePropertyEditor;

class DistributionWidget : public QWidget
{
    Q_OBJECT

public:
    DistributionWidget(QWidget *parent = 0);
    virtual ~DistributionWidget() {}

    QCustomPlot *getPlot() const;
    void setItem(DistributionItem *item);
    void plotItem(DistributionItem *item);

private slots:
    void onPropertyChanged(const QString &property_name);

private:
    QCustomPlot *m_plot;
    DistributionItem *m_item;

};

#endif
