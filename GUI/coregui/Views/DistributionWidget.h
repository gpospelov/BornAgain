#ifndef DISTRIBUTIONWIDGET_H_
#define DISTRIBUTIONWIDGET_H_


#include "qcustomplot.h"
#include "DistributionItem.h"
#include <QLabel>
#include <sstream>

class ParameterizedItem;
class AwesomePropertyEditor;
class QLabel;

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

public slots:
    void onMouseMove(QMouseEvent *event);
private slots:
    void onPropertyChanged();
    void movePoint(QMouseEvent *e);

private:
    QCustomPlot *m_plot;
    DistributionItem *m_item;
    // FIXME Do you need m_x and m_y to be class members?
    double m_x;
    double m_y;
    QLabel *m_label;

};

#endif
