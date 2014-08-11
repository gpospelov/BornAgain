#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include "OutputDataItem.h"
#include "centralplot.h"


#include <QWidget>
#include <QSplitter>
#include <QMouseEvent>


class HistogramPlot;


class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWidget(QWidget *parent=0, bool isContextMenuEnabled = true);
    virtual ~PlotWidget(){}

    QSize minimumSizeHint() const { return QSize(800, 800); }

    int histogramSize;
    void drawPlot(OutputDataItem *outputDataItem);

signals:
    void isProjectionsChanged(bool projection);

public slots:
    void onZaxisRangeChanged(QCPRange newRange);
    void updatePlot();

    void resetTriggered();
    void savePlot();
    void projectionsChanged(bool projection);
    void gradientChanged(QCPColorGradient gradient);

private slots:
    void mousePress(QMouseEvent*event);
    void mouseMove(QMouseEvent*event);
    void onXaxisRangeChanged(QCPRange newRange);
    void onYaxisRangeChanged(QCPRange newRange);

private:
    void initContextMenu();
    QSplitter *m_splitter;
    QSplitter *m_splitterTop;
    QSplitter *m_splitterBottom;
    CentralPlot *m_centralPlot;
    HistogramPlot *m_verticalPlot;
    HistogramPlot *m_horizontalPlot;
    QLabel *m_statusLabel;
    OutputDataItem *m_outputDataItem;
    QCPColorGradient m_gradient;
    bool m_block_plot_update;
    QAction *propertyPanelAct;
    QAction *projectionsAct;
    QAction *resetAct;
    QAction *saveAct;
    QMouseEvent *m_mouseEvent;
    QMenu *m_contextMenu;


    bool m_isProjectionsEnabled;
    bool m_isContextMenuEnabled;


};

#endif // PLOTWIDGET_H
