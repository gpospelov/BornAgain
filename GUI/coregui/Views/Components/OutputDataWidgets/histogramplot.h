#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include "centralplot.h"

class HistogramPlot : public QCustomPlot
{
    Q_OBJECT

public:
    enum PlotType{
        Vertical, Horizontal
    };

    HistogramPlot(){}
    HistogramPlot(PlotType type);




    void generateHistogram(const QVector<double> x, const QVector<double> y);
    void setupMap(CentralPlot *centralPlot);

private:
    void setupVerticalMap(CentralPlot *centralPlot, double min = 0, double max = 1);
    void setupHorizontalMap(CentralPlot *centralPlot, double min = 0, double max = 1);
    PlotType m_type;
    double min, max;


};

#endif // HISTOGRAMPLOT_H
