#include "DistributionWidget.h"

namespace {
int number_of_points_for_smooth_plot = 100;
double gap_between_bars = 0.001;
}

DistributionWidget::DistributionWidget(QWidget *parent)
    : m_plot(new QCustomPlot)
    , m_item(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_plot);
    setLayout(mainLayout);

}

QCustomPlot *DistributionWidget::getPlot() const
{
    return m_plot;
}

void DistributionWidget::setItem(DistributionItem *item)
{
    if (m_item == item) return;

    if (m_item) {
//        disconnect(m_item, SIGNAL(propertyChanged(QString)),
//                this, SLOT(onPropertyChanged(QString)));
        disconnect();
    }

    m_item = item;

    if (!m_item) return;

    plotItem(m_item);

    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
}

void DistributionWidget::plotItem(DistributionItem *item)
{
    m_plot->clearGraphs();
    m_plot->removePlottable(0);

    int numberOfSamples = m_item->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigmafactor = m_item->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();
    IDistribution1D *distribution = m_item->createDistribution();
    QVector<double> xbars;
    QVector<double> x;
    xbars = xbars.fromStdVector(distribution->generateValueList(number_of_points_for_smooth_plot, sigmafactor));
    x = x.fromStdVector(distribution->generateValueList(numberOfSamples, sigmafactor));
    QVector<double> ybars(xbars.size());
    QVector<double> y(x.size());
    for(int i = 0; i < xbars.size(); ++i) {
        ybars[i] = distribution->probabilityDensity(xbars[i]);
    }
    for(int i = 0; i < x.size(); ++i) {
        y[i] = distribution->probabilityDensity(x[i]);
    }
    m_plot->addGraph();
    m_plot->graph(0)->setData(xbars,ybars);
    m_plot->xAxis->setLabel("x");
    m_plot->yAxis->setLabel("y");
    m_plot->rescaleAxes();
    QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
    bars1->setWidth(gap_between_bars/x.size());
    bars1->setData(x, y);
    m_plot->addPlottable(bars1);
    m_plot->replot();

}

void DistributionWidget::onPropertyChanged(const QString &property_name)
{
    plotItem(m_item);
}
