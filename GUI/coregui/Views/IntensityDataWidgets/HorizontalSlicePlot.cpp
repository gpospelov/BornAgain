// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/HorizontalSlicePlot.cpp
//! @brief     Implements class HorizontalSlicePlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "HorizontalSlicePlot.h"
#include "AxesItems.h"
#include "IntensityDataItem.h"
#include "MathConstants.h"
#include "qcustomplot.h"
#include <QVBoxLayout>

HorizontalSlicePlot::HorizontalSlicePlot(QWidget *parent)
    : QWidget(parent)
    , m_customPlot(0)
    , m_bars(0)
    , m_item(0)
//    , m_mapper(0)
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

void HorizontalSlicePlot::setItem(IntensityDataItem *item)
{
    if(m_item == item) {
        return;

    } else {
        if(m_item)
            m_item->mapper()->unsubscribe(this);

        m_item = item;
        if (!m_item) return;

        plotItem(m_item);

        m_item->mapper()->setOnChildPropertyChange(
                    [this](SessionItem* item, const QString name)
        {
            if (item->parent() && item->parent()->modelType() == Constants::GroupItemType)
                onSubItemPropertyChanged(item->itemName(), name);
        }, this);
    }


}

void HorizontalSlicePlot::plotData(const QVector<double> &x, const QVector<double> &y)
{
    //qDebug() << "NHistogramPlot::plotData(const QVector<double> &x, const QVector<double> &y)";
    m_bars->setData(x, y);
    m_customPlot->replot();
}

void HorizontalSlicePlot::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "HorizontalSlicePlot::onSubItemPropertyChanged(const QString &property_name)" << property_group << property_name;
    if(property_group == IntensityDataItem::P_XAXIS) {
        if(property_name == BasicAxisItem::P_MIN) {
            setXmin(m_item->getLowerX());
        }
        else if(property_name == BasicAxisItem::P_MAX) {
            setXmax(m_item->getUpperX());
        }
    }
    else if(property_group == IntensityDataItem::P_YAXIS) {
        if(property_name == BasicAxisItem::P_MIN) {
            setYmin(m_item->getLowerY());
        }
        else if(property_name == BasicAxisItem::P_MAX) {
            setYmax(m_item->getUpperY());
        }
    }
    else if(property_group == IntensityDataItem::P_ZAXIS) {
        if(property_name == BasicAxisItem::P_MIN) {
            setZmin(m_item->getLowerZ());
        }
        else if(property_name == BasicAxisItem::P_MAX) {
            setZmax(m_item->getUpperZ());
        }
        else if(property_name == AmplitudeAxisItem::P_IS_LOGSCALE) {
            setLogz(m_item->isLogz(), true);
        }
    }
}

void HorizontalSlicePlot::plotItem(IntensityDataItem *intensityItem)
{
    //qDebug() << "NHistogramPlot::plotItem(NIntensityDataItem *intensityItem)";
    Q_ASSERT(intensityItem);

    const OutputData<double> *data = intensityItem->getOutputData();
    if(!data) return;

    if(data->getRank() != 2) {
        throw Exceptions::NullPointerException("NHistogramPlot::plotItem::Draw() -> Error. Zero pointer to the data to draw");
    }

    m_customPlot->axisRect()->setupFullAxesBox(true);

    m_customPlot->xAxis->setRange(intensityItem->getLowerX(), intensityItem->getUpperX());
    m_customPlot->yAxis->setRange(intensityItem->getLowerZ(), intensityItem->getUpperZ());

    const IAxis &axis0 = data->getAxis(0);
    double bin_size(0);
    bin_size = (axis0.getMax() - axis0.getMin())/axis0.size();

    m_bars->setWidth(bin_size);
    m_bars->setPen(Qt::NoPen);
    m_bars->setBrush(Qt::blue);

    setLogz(intensityItem->isLogz());

//    const QMargins margins(0,0,82,0);
    const QMargins margins(10,0,77,0);
    m_customPlot->axisRect()->setMargins(margins);
    m_customPlot->axisRect()->layout()->setMargins(margins);

    m_customPlot->replot();
}


void HorizontalSlicePlot::setLogz(bool logz, bool isReplot)
{
    if(logz) {
        m_customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
        m_customPlot->yAxis->setNumberFormat("eb");
        m_customPlot->yAxis->setNumberPrecision(0);
    } else {
        m_customPlot->yAxis->setScaleType(QCPAxis::stLinear);
        m_customPlot->yAxis->setNumberFormat("f");
    }

    if(isReplot) m_customPlot->replot();
}

void HorizontalSlicePlot::setXmin(double value)
{
    QCPRange range = m_customPlot->xAxis->range();
    range.lower = value;
    m_customPlot->xAxis->setRange(range);
    m_customPlot->replot();
}

void HorizontalSlicePlot::setXmax(double value)
{
    QCPRange range = m_customPlot->xAxis->range();
    range.upper = value;
    m_customPlot->xAxis->setRange(range);
    m_customPlot->replot();
}

void HorizontalSlicePlot::setYmin(double value)
{
    Q_UNUSED(value);
//    QCPRange range = m_customPlot->yAxis->range();
//    range.lower = value;
//    m_customPlot->yAxis->setRange(range);
//    m_customPlot->replot();
}

void HorizontalSlicePlot::setYmax(double value)
{
    Q_UNUSED(value);
//    QCPRange range = m_customPlot->yAxis->range();
//    range.upper = value;
//    m_customPlot->yAxis->setRange(range);
//    m_customPlot->replot();
}

void HorizontalSlicePlot::setZmin(double value)
{
    QCPRange range = m_customPlot->yAxis->range();
    range.lower = value;
    m_customPlot->yAxis->setRange(range);
    m_customPlot->replot();
}

void HorizontalSlicePlot::setZmax(double value)
{
    QCPRange range = m_customPlot->yAxis->range();
    range.upper = value;
    m_customPlot->yAxis->setRange(range);
    m_customPlot->replot();
}
