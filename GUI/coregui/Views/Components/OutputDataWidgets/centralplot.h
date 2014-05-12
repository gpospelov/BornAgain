#ifndef CENTRALPLOT_H
#define CENTRALPLOT_H

#include "qcustomplot.h"
#include "qcpdocumentobject.h"
#include <sstream>
#include "OutputDataItem.h"

class CentralPlot : public QCustomPlot
{
    Q_OBJECT

public:
    CentralPlot();

    //void drawGraphOnMouseEvent(QPoint point, HistogramPlot *verticalPlot, HistogramPlot *horizontalPlot);
    void drawGraphOnMouseEvent(QPoint point);
    bool contains(QPoint point);
    QVector<QVector<double> > getHistogramData(QPoint point, bool isDrawLine = true);
    void drawPlot(OutputDataItem *outputDataItem, QCPColorGradient gradient);

    //QCPColorScale *getColorScale() const;
    QCPColorMap *getColorMap() const;
    QCPRange getColorScaleRange() const;
    QCPColorMapData *getColorMapData() const;
    QString getStatusString() const;
    void setInterpolate(bool isInterpolate);
    void setZmin(double zmin);
    void setZmax(double zmax);
    void resetView();
    void setGradient(QCPColorGradient gradient);
    void setLogz(bool logz, bool isReplot  = true);
    bool isLogz();

signals:
    void dataRangeChanged(QCPRange newRange);

private:
    void setupColorMap(CentralPlot * customPlot);
    void drawLineOverColorMap(double xPos, double yPos);
    QCPColorMap *m_colorMap;
    QCPColorScale *m_colorScale;
    QString statusString;
    QCPRange m_colorScaleRange;
    OutputDataItem *m_outputDataItem;
    QCPRange calculateDataRange();

};

#endif // CENTRALPLOT_H
