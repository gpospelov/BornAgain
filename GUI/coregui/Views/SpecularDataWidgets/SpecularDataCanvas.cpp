// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.cpp
//! @brief     Implements class SpecularDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ColorMapUtils.h"
#include "SpecularDataCanvas.h"
#include "SpecularDataItem.h"
#include "plot_constants.h"

SpecularDataCanvas::SpecularDataCanvas(QWidget* parent)
    : QWidget(parent), m_customPlot(new QCustomPlot)

{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);
    setStyleSheet("background-color:white;");

    initGraph();

    m_customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));
    m_customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));

    ColorMapUtils::setLogz(m_customPlot->yAxis, true);

    m_customPlot->xAxis->setLabel("iteration");
    m_customPlot->yAxis->setLabel("chi2");

    m_customPlot->xAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
    m_customPlot->yAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
}

void SpecularDataCanvas::setData(SpecularDataItem* data_item)
{
    m_data_item = data_item;
    initGraphFromItem();
}

void SpecularDataCanvas::clearData()
{
    m_customPlot->removeGraph(m_customPlot->graph());
    initGraph();
    m_customPlot->replot();
}

void SpecularDataCanvas::initGraph()
{
    m_customPlot->addGraph();

    QPen pen(QColor(0, 0, 255, 200));
    m_customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    m_customPlot->graph()->setPen(pen);

    QFontMetrics fontMetric(font());
    auto em = fontMetric.width('M'), fontAscent = fontMetric.ascent();
    auto* axisRectangle = m_customPlot->axisRect();
    axisRectangle->setAutoMargins(QCP::msTop | QCP::msBottom);
    axisRectangle->setMargins(QMargins(em*4, fontAscent*2, em*2, fontAscent*2));
}

void SpecularDataCanvas::initGraphFromItem()
{
    const auto underlying_data = intensityData()->getOutputData();
    for (size_t i = 0, size = underlying_data->getAllocatedSize(); i < size; ++i) {
        double x = underlying_data->getAxisValue(i, 0);
        double y = underlying_data->operator[](i);
        m_customPlot->graph()->addData(x, y);
    }
}
