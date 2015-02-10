// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/NHistogramPlot.cpp
//! @brief     Implements class NHistogramPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "NHistogramPlot.h"
#include "NIntensityDataItem.h"
#include "qcustomplot.h"
#include "Units.h"
#include <QVBoxLayout>

NHistogramPlot::NHistogramPlot(QWidget *parent)
    : QWidget(parent)
    , m_customPlot(0)
    , m_bars(0)
    , m_item(0)
{
    m_customPlot = new QCustomPlot();
    m_bars = new QCPBars(m_customPlot->xAxis, m_customPlot->yAxis);
    m_customPlot->addPlottable(m_bars);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);

}

void NHistogramPlot::setItem(NIntensityDataItem *item)
{
    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
    }

    m_item = item;

    if (!m_item) return;

    plotItem(m_item);

    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));

}

void NHistogramPlot::plotData(const QVector<double> &x, const QVector<double> &y)
{
    qDebug() << "NHistogramPlot::plotData(const QVector<double> &x, const QVector<double> &y)";
    m_bars->setData(x, y);
    m_customPlot->replot();
}

void NHistogramPlot::onPropertyChanged(const QString &property_name)
{
    qDebug() << "NHistogramPlot::onPropertyChanged(const QString &property_name)";

    if(property_name == NIntensityDataItem::P_IS_LOGZ) {
        setLogz(m_item->isLogz(), true);
    } else if(property_name == NIntensityDataItem::P_XAXIS_MIN) {
        setXmin(m_item->getXaxisMin());
    } else if(property_name == NIntensityDataItem::P_XAXIS_MAX) {
        setXmax(m_item->getXaxisMax());
    } else if(property_name == NIntensityDataItem::P_ZAXIS_MIN) {
        setYmin(m_item->getZaxisMin());
    } else if(property_name == NIntensityDataItem::P_ZAXIS_MAX) {
        setYmax(m_item->getZaxisMax());
    }



}

void NHistogramPlot::plotItem(NIntensityDataItem *intensityItem)
{
    qDebug() << "NHistogramPlot::plotItem(NIntensityDataItem *intensityItem)";
    Q_ASSERT(intensityItem);

    const OutputData<double> *data = intensityItem->getOutputData();
    Q_ASSERT(data);

    if(data->getRank() != 2) {
        throw NullPointerException("NHistogramPlot::plotItem::Draw() -> Error. Zero pointer to the data to draw");
    }

    m_customPlot->xAxis->setRange(intensityItem->getXaxisMin(), intensityItem->getXaxisMax());
    m_customPlot->yAxis->setRange(intensityItem->getZaxisMin(), intensityItem->getZaxisMax());

    const IAxis *axis0 = data->getAxis(0);
    double bin_size(0);
    if(intensityItem->axesInRadians()) {
        bin_size = (axis0->getMax() - axis0->getMin())/axis0->getSize();
    } else {
        bin_size = (Units::rad2deg(axis0->getMax()) - Units::rad2deg((axis0->getMin())))/axis0->getSize();
    }

    m_bars->setWidth(bin_size);
    m_bars->setPen(Qt::NoPen);
    m_bars->setBrush(Qt::blue);

    setLogz(intensityItem->isLogz());

    const QMargins margins(0,0,82,0);
    m_customPlot->axisRect()->setMargins(margins);
    m_customPlot->axisRect()->layout()->setMargins(margins);

    m_customPlot->replot();
}


void NHistogramPlot::setLogz(bool logz, bool isReplot)
{
    if(logz) {
        m_customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    } else {
        m_customPlot->yAxis->setScaleType(QCPAxis::stLinear);
    }

    if(isReplot) m_customPlot->replot();
}

void NHistogramPlot::setXmin(double value)
{
    QCPRange range = m_customPlot->xAxis->range();
    range.lower = value;
    m_customPlot->xAxis->setRange(range);
    m_customPlot->replot();
}

void NHistogramPlot::setXmax(double value)
{
    QCPRange range = m_customPlot->xAxis->range();
    range.upper = value;
    m_customPlot->xAxis->setRange(range);
    m_customPlot->replot();
}

void NHistogramPlot::setYmin(double value)
{
    QCPRange range = m_customPlot->yAxis->range();
    range.lower = value;
    m_customPlot->yAxis->setRange(range);
    m_customPlot->replot();
}

void NHistogramPlot::setYmax(double value)
{
    QCPRange range = m_customPlot->yAxis->range();
    range.upper = value;
    m_customPlot->yAxis->setRange(range);
    m_customPlot->replot();
}
