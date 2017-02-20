// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ProjectionCanvas.h
//! @brief     Defines class ProjectionCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsPlot.h"
#include "qcustomplot.h"
#include "plot_constants.h"
#include "ProjectionItems.h"

ProjectionsPlot::ProjectionsPlot(QWidget* parent)
    : SessionItemWidget(parent)
    , m_customPlot(new QCustomPlot)
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);

//    m_customPlot->addGraph();
//    QPen pen;
//    pen.setColor(QColor(0, 0, 255, 200));
//    m_customPlot->graph()->setLineStyle(QCPGraph::lsLine);
//    m_customPlot->graph()->setPen(pen);
//    m_customPlot->graph()->setBrush(QBrush(QColor(255/4.0,160,50,150)));

//    m_customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));
//    m_customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));

//    m_customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
//    m_customPlot->yAxis->setNumberFormat("eb");
//    m_customPlot->yAxis->setNumberPrecision(0);

//    m_customPlot->xAxis->setLabel("iteration");
//    m_customPlot->yAxis->setLabel("chi2");

//    m_customPlot->xAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
    //    m_customPlot->yAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
}

void ProjectionsPlot::setItem(SessionItem* projectionContainerItem)
{
    Q_ASSERT(projectionContainerItem);
    SessionItemWidget::setItem(projectionContainerItem);

    qDebug() << projectionContainerItem->modelType();
}
