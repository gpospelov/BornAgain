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
    qDebug() << "ProjectionsPlot::subscribeToItem()" << m_projectionType;

    // Update projection plot on new item appearance
    projectionContainerItem()->mapper()->setOnChildrenChange(
        [this](SessionItem* item) {
            if(item)
                updateProjections();
        }, this);

    // Remove projection plot
    projectionContainerItem()->mapper()->setOnAboutToRemoveChild(
        [this](SessionItem* item) {
            clearProjection(item);
        }, this);

    // Update projection position
    projectionContainerItem()->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString& name) {
            onProjectionPropertyChanged(item, name);
        }, this);

    // Intensity data changed, regenerate everything
    intensityItem()->mapper()->setOnValueChange(
        [this]() {
            updateProjectionsData();
            updateProjections();
        }, this);

    // IntensityItem property (e.g. interpolation changed)
    intensityItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            onIntensityItemPropertyChanged(name);
    }, this);


    updateProjectionsData();
    updateProjections();
}

void ProjectionsPlot::unsubscribeFromItem()
{
    qDebug() << "ProjectionsPlot::unsubscribeFromItem()" << m_projectionType;
    if(currentItem())
        projectionContainerItem()->mapper()->unsubscribe(this);
}

void ProjectionsPlot::onProjectionPropertyChanged(SessionItem* item, const QString& property)
{
    if(m_block_plot_update)
        return;

    m_block_plot_update = true;

    if (property == HorizontalLineItem::P_POSY || property == VerticalLineItem::P_POSX) {
        if(auto graph = graphForItem(item))
            setGraphFromItem(graph, item);

        replot();
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
    return projectionContainerItem()->getChildrenOfType(m_projectionType);
}

QCPGraph* ProjectionsPlot::graphForItem(SessionItem* item)
{
    if(item->modelType() != m_projectionType)
        return nullptr;

    QCPGraph *graph = m_item_to_graph[item];
    if (!graph) {
        graph = m_customPlot->addGraph();
        QPen pen;
        pen.setColor(QColor(0, 0, 255, 200));
        graph->setLineStyle(intensityItem()->isInterpolated() ? QCPGraph::lsLine
                                                              : QCPGraph::lsStepCenter);

        graph->setPen(pen);
//        graph->setBrush(QBrush(QColor(255/4.0,160,50,150)));
        m_item_to_graph[item] = graph;
    }

    return graph;
}

//! Creates cached 2D histogram for later projection calculations.

void ProjectionsPlot::updateProjectionsData()
{
    m_hist2d.reset(new Histogram2D(*intensityItem()->getOutputData()));
    m_customPlot->yAxis->setRange(ColorMapUtils::itemDataRange(intensityItem()));

    if (m_projectionType == Constants::HorizontalLineMaskType) {
        m_customPlot->xAxis->setRange(ColorMapUtils::itemXrange(intensityItem()));
    } else {
        m_customPlot->xAxis->setRange(ColorMapUtils::itemYrange(intensityItem()));
    }
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

    replot();

    m_block_plot_update = false;
    qDebug() << "ProjectionsPlot::updateProjections() 3.3";
}

//! Clears all graphs corresponding to projection items.

void ProjectionsPlot::clearProjections()
{
    m_block_plot_update = true;

    m_customPlot->clearPlottables();
    m_item_to_graph.clear();

    replot();

    m_block_plot_update = false;
}

//! Removes plot corresponding to given projection item.

void ProjectionsPlot::clearProjection(SessionItem* item)
{
    if (auto graph = graphForItem(item)) {
        m_block_plot_update = true;
        m_customPlot->removePlottable(graph);
        m_item_to_graph.remove(item);
        replot();
        m_block_plot_update = false;
    }
}

//! Updates projection appearance (line style, etc)

void ProjectionsPlot::onIntensityItemPropertyChanged(const QString& propertyName)
{
    if (propertyName == IntensityDataItem::P_IS_INTERPOLATED) {
        setInterpolate(intensityItem()->isInterpolated());
        replot();
    }

}

//! Sets the data to graph from given projection iten.

void ProjectionsPlot::setGraphFromItem(QCPGraph* graph, SessionItem* item)
{
    std::unique_ptr<Histogram1D> hist;

    if (item->modelType() == Constants::HorizontalLineMaskType) {
        double value  = item->getItemValue(HorizontalLineItem::P_POSY).toDouble();
        hist.reset(m_hist2d->projectionX(value));
    } else {
        double value  = item->getItemValue(VerticalLineItem::P_POSX).toDouble();
        hist.reset(m_hist2d->projectionY(value));
    }

    graph->setData(QVector<double>::fromStdVector(hist->getBinCenters()),
                   QVector<double>::fromStdVector(hist->getBinValues()));
}

void ProjectionsPlot::setInterpolate(bool isInterpolated)
{
    for(auto graph : m_item_to_graph)
        graph->setLineStyle(isInterpolated ? QCPGraph::lsLine : QCPGraph::lsStepCenter);
}

void ProjectionsPlot::replot()
{
    m_customPlot->replot();
}
