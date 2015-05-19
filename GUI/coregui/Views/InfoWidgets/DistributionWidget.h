#ifndef DISTRIBUTIONWIDGET_H_
#define DISTRIBUTIONWIDGET_H_


#include "qcustomplot.h"
#include "DistributionItem.h"
#include <QLabel>
#include <sstream>
#include <boost/scoped_ptr.hpp>

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
    void onMousePress(QMouseEvent *event);
private slots:
    void onPropertyChanged();
//    void movePoint(QMouseEvent *e);    
    void resetView();
private:
    QCustomPlot *m_plot;
    DistributionItem *m_item;
    QLabel *m_label;
    QAction m_resetAction;
    QCPRange *m_xRange;
    QCPRange *m_yRange;
};

#endif
