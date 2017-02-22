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
#include "MaskItems.h"
#include "ColorMapUtils.h"
#include <QDebug>

ProjectionsPlot::ProjectionsPlot(const QString& projectionType, QWidget* parent)
    : SessionItemWidget(parent)
    , m_projectionType(projectionType)
    , m_customPlot(new QCustomPlot)
    , m_block_plot_update(false)
{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);
}

ProjectionsPlot::~ProjectionsPlot()
{

}

void ProjectionsPlot::setItem(SessionItem* intensityItem)
{
    Q_ASSERT(intensityItem);
    SessionItemWidget::setItem(intensityItem);
}

void ProjectionsPlot::subscribeToItem()
{

    projectionContainerItem()->mapper()->setOnChildrenChange(
        [this](SessionItem* item) {
            // Removal of any child will regenerate all projections, apperance of a new child will
            // create missed projections
            item ? updateProjections() : clearProjections();
        }, this);

    projectionContainerItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString& name) {
            onProjectionPropertyChanged(item, name);
        }, this);

    intensityItem()->mapper()->setOnValueChange(
        [this]() {
            updateProjectionsData();
        }, this);

    updateProjectionsData();
}

void ProjectionsPlot::unsubscribeFromItem()
{
    if(currentItem())
        projectionContainerItem()->mapper()->unsubscribe(this);
}

void ProjectionsPlot::onProjectionPropertyChanged(SessionItem* item, const QString& property)
{
    qDebug() << "ProjectionsPlot::onProjectionPropertyChanged" << item->modelType() << property;

    if(m_block_plot_update)
        return;

    m_block_plot_update = true;

    if (property == HorizontalLineItem::P_POSY || property == VerticalLineItem::P_POSX) {
        QCPGraph* graph = graphForItem(item);
        setGraphFromItem(graph, item);

        m_customPlot->replot();
    }

    m_block_plot_update = false;
}

IntensityDataItem* ProjectionsPlot::intensityItem()
{
    IntensityDataItem* result = dynamic_cast<IntensityDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

ProjectionContainerItem* ProjectionsPlot::projectionContainerItem()
{
    ProjectionContainerItem* result = dynamic_cast<ProjectionContainerItem*>(
                intensityItem()->getItem(IntensityDataItem::T_PROJECTIONS));
    Q_ASSERT(result);
    return result;
}

QVector<SessionItem*> ProjectionsPlot::projectionItems()
{
    return projectionContainerItem()->getChildrenOfType(Constants::HorizontalLineMaskType);
}

QCPGraph* ProjectionsPlot::graphForItem(SessionItem* item)
{
    Q_ASSERT(item->modelType() == m_projectionType);

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

//! Creates cached 2D histogram for later projection calculations.

void ProjectionsPlot::updateProjectionsData()
{
    m_hist2d.reset(new Histogram2D(*intensityItem()->getOutputData()));
    m_customPlot->yAxis->setRange(ColorMapUtils::itemDataRange(intensityItem()));
    m_customPlot->xAxis->setRange(ColorMapUtils::itemXrange(intensityItem()));
    ColorMapUtils::setLogz(m_customPlot->yAxis, intensityItem()->isLogz());
}

//! Runs through all projection items and generates missed plots.

void ProjectionsPlot::updateProjections()
{
    if(m_block_plot_update)
        return;

    m_block_plot_update = true;

    for(auto projItem : projectionItems())
        setGraphFromItem(graphForItem(projItem), projItem);

    m_customPlot->replot();

    m_block_plot_update = false;
}

//! Clears all graphs corresponding to projection items.

void ProjectionsPlot::clearProjections()
{
    m_block_plot_update = true;

    m_customPlot->clearPlottables();
    m_item_to_graph.clear();

    m_customPlot->replot();

    m_block_plot_update = false;
}

//! Sets the data to graph from given projection iten.

void ProjectionsPlot::setGraphFromItem(QCPGraph* graph, SessionItem* item)
{
    std::unique_ptr<Histogram1D> hist;

    if(item->modelType() == Constants::HorizontalLineMaskType) {
        double value  = item->getItemValue(HorizontalLineItem::P_POSY).toDouble();
        hist.reset(m_hist2d->projectionX(value));
    } else {
        double value  = item->getItemValue(VerticalLineItem::P_POSX).toDouble();
        hist.reset(m_hist2d->projectionY(value));
    }

    graph->setData(QVector<double>::fromStdVector(hist->getBinCenters()),
                   QVector<double>::fromStdVector(hist->getBinValues()));
}
