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
    explicit PlotWidget(QWidget *parent, bool isCreateToolbar = true);
    virtual ~PlotWidget(){}

    QSize minimumSizeHint() const { return QSize(800, 800); }

    int histogramSize;
    void drawPlot(OutputDataItem *outputDataItem);


public slots:
    void onZaxisRangeChanged(QCPRange newRange);
    void updatePlot();

private slots:
    void mousePress(QMouseEvent*event);
    void mouseMove(QMouseEvent*event);
    void resetTriggered();
    void togglePropertyPanel();
    void savePlot();
    void projectionsChanged(bool projection);
    void gradientChanged(QCPColorGradient gradient);
    void toggleProjections();

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
    void connectToobarSignals();
    OutputDataItem *m_outputDataItem;
    QCPColorGradient m_gradient;
    bool m_block_plot_update;
    QAction *propertyPanelAct;
    QAction *projectionsAct;
    QAction *resetAct;
    QAction *saveAct;

    bool isPropertyWidgetVisible;
    bool isProjectionsVisible;


};

#endif // PLOTWIDGET_H
