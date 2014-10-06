#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include "OutputDataItem.h"
#include "centralplot.h"
#include <QWidget>
#include <QSplitter>
#include <QMouseEvent>

class HistogramPlot;
class ProjectManager;

class BA_CORE_API_ PlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWidget(QWidget *parent=0, bool isContextMenuEnabled = true, bool isProjectionsEnabled = true);
    virtual ~PlotWidget(){}

    QSize minimumSizeHint() const { return QSize(800, 800); }

    int histogramSize;
    void drawPlot(OutputDataItem *outputDataItem);
    void setPropertyWidgetVisibilityFlag(bool visible);
    void setProjectManager(ProjectManager *projectManager);

signals:
    void projectionsVisibilityChanged(bool visible);
    void propertyWidgetVisibilityChanged(bool visible);

public slots:
    void onZaxisRangeChanged(QCPRange newRange);
    void updatePlot();
    void updateIntensity();

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
    void connectSignals();
    void showProjectsions(bool visible);


    QSplitter *m_splitter;
    QSplitter *m_splitterTop;
    QSplitter *m_splitterBottom;
    CentralPlot *m_centralPlot;
    HistogramPlot *m_verticalPlot;
    HistogramPlot *m_horizontalPlot;
    QLabel *m_statusLabel;
    OutputDataItem *m_outputDataItem;
    QCPColorGradient m_gradient;

    QAction *m_propertyPanelAction;
    QAction *m_projectionsAction;
    QAction *m_resetAction;
    QAction *m_saveAction;
    QMenu *m_contextMenu;
    ProjectManager *m_projectManager;

    bool m_block_plot_update;
    bool m_isProjectionsEnabled;
    bool m_isContextMenuEnabled;
    bool m_isPropertyWidgetVisible;


};

#endif // PLOTWIDGET_H
