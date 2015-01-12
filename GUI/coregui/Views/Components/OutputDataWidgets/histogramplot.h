#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include "centralplot.h"

class BA_CORE_API_ HistogramPlot : public QCustomPlot
{
    Q_OBJECT

public:
    enum EPlotType{ VERTICAL, HORIZONTAL };

    HistogramPlot(){}
    HistogramPlot(EPlotType type);

    //QSize sizeHint() const { return QSize(150, 600); }

    void generateHistogram(const QVector<double> x, const QVector<double> y);
    void setupMap(CentralPlot *centralPlot);
    void setLogz(bool logz, bool isReplot = true);
    void setColorScaleRange(double lower, double upper);
    void setKeyAxisRange(QCPRange newRange);

private:
    void setupVerticalMap(CentralPlot *centralPlot, double min = 0, double max = 1);
    void setupHorizontalMap(CentralPlot *centralPlot, double min = 0, double max = 1);
    EPlotType m_type;
    double min, max;
    QCPAxis *m_dataScaleAxis;
    QCPAxis *m_keyAxis;

};

#endif // HISTOGRAMPLOT_H
