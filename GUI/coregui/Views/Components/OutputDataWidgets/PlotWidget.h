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
#include "OutputDataToolBar.h"


class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWidget(QWidget *parent);
    virtual ~PlotWidget(){}

    QSize minimumSizeHint() const { return QSize(600, 600); }

    int histogramSize;
    void drawPlot(OutputDataItem *outputDataItem);
    void updatePlot();


public slots:
    void onZaxisRangeChanged(QCPRange newRange);

private slots:
    void mousePress(QMouseEvent*event);
    void mouseMove(QMouseEvent*event);
    void resetTriggered();
    void togglePropertypanel();
    void savePlot();
    void projectionsChanged(bool projection);
    void gradientChanged(QCPColorGradient gradient);


private:
    QSplitter *m_splitter;
    QSplitter *m_splitterRight;
    QSplitter *m_splitterLeft;
    QSplitter *m_splitterTop;
    QSplitter *m_splitterBottom;
    CentralPlot *m_centralPlot;
    HistogramPlot *m_verticalPlot;
    HistogramPlot *m_horizontalPlot;
    QLabel *m_statusLabel;
    PropertyWidget *m_propertyWidget;
    OutputDataToolBar *m_toolBar;
    void connectSignals();
    OutputDataItem *m_outputDataItem;
    QCPColorGradient m_gradient;


};

#endif // PLOTWIDGET_H
