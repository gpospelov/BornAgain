#include "DistributionPlotwidget.h"

DistributionPlotWidget::DistributionPlotWidget(QWidget *parent)
    : m_plot(new QCustomPlot)
{

}

QCustomPlot *DistributionPlotWidget::getPlot() const
{
    return m_plot;
}
