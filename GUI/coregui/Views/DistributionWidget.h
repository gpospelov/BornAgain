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
    void setItem(DistributionItem *item);
    void plotItem();
    double getWidthOfBars(double min, double max, int samples);
    void setVerticalDashedLine(double xMin, double yMin, double xMax, double yMax);
    int getMaxYPosition(int y);

private slots:
    void onPropertyChanged();
    void movePoint(QMouseEvent *e);


private:
    QCustomPlot *m_plot;
    DistributionItem *m_item;
    double m_x;
    double m_y;

};

#endif
