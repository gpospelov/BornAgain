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
#include "SessionItem.h"
#include "ModelMapper.h"
#include "IntensityDataItem.h"
#include "Histogram1D.h"
#include "Histogram2D.h"
#include <QDebug>

ProjectionsPlot::ProjectionsPlot(QWidget* parent)
    : SessionItemWidget(parent)
    , m_customPlot(new QCustomPlot)
    , m_block_plot_update(false)
{
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);
}

ProjectionsPlot::~ProjectionsPlot()
{

}

void ProjectionsPlot::setItem(SessionItem* projectionContainerItem)
{
    Q_ASSERT(projectionContainerItem);
    SessionItemWidget::setItem(projectionContainerItem);

    qDebug() << projectionContainerItem->modelType();
}

void ProjectionsPlot::subscribeToItem()
{
    currentItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString name) {
            onChildPropertyChanged(item, name);
        },
        this);

    m_hist2d.reset(new Histogram2D(*intensityItem()->getOutputData()));

}

void ProjectionsPlot::unsubscribeFromItem()
{

}

void ProjectionsPlot::onChildPropertyChanged(SessionItem* item, const QString& property)
{
    if(m_block_plot_update)
        return;

    m_block_plot_update = true;

    Q_ASSERT(item);
    double y = item->getItemValue(property).toDouble();


    QCPGraph* graph = addGraphForItem(item);
    Q_ASSERT(graph);
    qDebug() << "ProjectionsPlot::onChildPropertyChanged" << item->modelType() << property << y << graph;

    std::unique_ptr<Histogram1D> hist(m_hist2d->projectionX(y));

    graph->setData(QVector<double>::fromStdVector(hist->getBinCenters()), QVector<double>::fromStdVector(hist->getBinValues()));
    graph->rescaleAxes();
    m_customPlot->replot();
    m_block_plot_update = false;
}

IntensityDataItem* ProjectionsPlot::intensityItem()
{
    IntensityDataItem* result = dynamic_cast<IntensityDataItem*>(currentItem()->parent());
    Q_ASSERT(result);
    return result;
}

QCPGraph* ProjectionsPlot::addGraphForItem(SessionItem* item)
{
    Q_ASSERT(item->modelType() == Constants::HorizontalLineMaskType);

    QCPGraph *graph = m_item_to_graph[item];
    if (!graph) {
        graph = m_customPlot->addGraph();
        QPen pen;
        pen.setColor(QColor(0, 0, 255, 200));
        graph->setLineStyle(QCPGraph::lsLine);
        graph->setPen(pen);
        graph->setBrush(QBrush(QColor(255/4.0,160,50,150)));
        m_item_to_graph[item] = graph;
    }
    return graph;
}
