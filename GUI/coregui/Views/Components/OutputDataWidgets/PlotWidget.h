#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include "centralplot.h"
#include "histogramplot.h"
#include "QMouseEvent"
#include "OutputData.h"
#include "PropertyWidget.h"
#include "OutputDataItem.h"


class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWidget(QWidget *parent);
    virtual ~PlotWidget(){}

    QSize minimumSizeHint() const { return QSize(800, 600); }

    int histogramSize;



    void toggleHistogram();
    void drawPlot(OutputDataItem *m_outputDataItem);


private slots:
    void mousePress(QMouseEvent*event);
    void mouseMove(QMouseEvent*event);


private:
    QSplitter *m_splitter;
    QSplitter *m_splitterRight;
    QSplitter *m_splitterLeft;
    QSplitter *m_splitterTop;
    QSplitter *m_splitterBottom;
    CentralPlot *m_centralPlot;
    HistogramPlot *m_verticalPlot;
    HistogramPlot *m_horizontalPlot;
    QLabel *statusLabel;
    PropertyWidget *m_propertyWidget;




};

#endif // PLOTWIDGET_H
