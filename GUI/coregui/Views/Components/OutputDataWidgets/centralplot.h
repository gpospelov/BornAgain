#ifndef CENTRALPLOT_H
#define CENTRALPLOT_H

#include "qcustomplot.h"
#include "qcpdocumentobject.h"
#include <sstream>
#include "OutputData.h"

class CentralPlot : public QCustomPlot
{
    Q_OBJECT

public:
    CentralPlot();

    //void drawGraphOnMouseEvent(QPoint point, HistogramPlot *verticalPlot, HistogramPlot *horizontalPlot);
    void drawGraphOnMouseEvent(QPoint point);
    bool contains(QPoint point);
    QVector<QVector<double> > getHistogramData(QPoint point, bool isDrawLine = true);
    void drawPlot(const OutputData<double> *data);

    //QCPColorScale *getColorScale() const;
    QCPColorMap *getColorMap() const;
    QCPRange getColorScaleRange() const;
    QCPColorMapData *getColorMapData() const;
    QString getStatusString() const;
    void setInterpolate(bool isInterpolate);
    void setZmin(double zmin);
    void setZmax(double zmax);
    void resetView();

signals:
    void dataRangeChanged(QCPRange newRange);

private:
    void setupColorMap(CentralPlot * customPlot);
    void drawLineOverColorMap(double xPos, double yPos);
    QCPColorMap *colorMap;
    QCPColorScale *colorScale;
    QString statusString;
    QCPRange m_colorScaleRange;
};

#endif // CENTRALPLOT_H
