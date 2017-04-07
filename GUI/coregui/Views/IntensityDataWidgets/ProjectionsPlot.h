// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ProjectionsPlot.h
//! @brief     Defines class ProjectionsPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSPLOT_H
#define PROJECTIONSPLOT_H

#include "SessionItemWidget.h"
#include "qcustomplot.h"
#include <memory>
#include <QMap>

class IntensityDataItem;
class ProjectionContainerItem;
class Histogram2D;
class QCPGraph;

//! A customplot based widget to display projections of IntensityDataItem on X,Y axes.

class BA_CORE_API_ ProjectionsPlot : public SessionItemWidget
{
    Q_OBJECT

public:
    ProjectionsPlot(const QString& projectionType, QWidget* parent = 0);
    virtual ~ProjectionsPlot();

    void setItem(SessionItem* intensityItem);

public slots:
    void onMarginsChanged(double left, double right);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

    void onProjectionPropertyChanged(SessionItem* item, const QString& property);

private:
    IntensityDataItem* intensityItem();
    ProjectionContainerItem* projectionContainerItem();
    QVector<SessionItem*> projectionItems();
    QCPGraph* graphForItem(SessionItem* item);

    void updateProjectionsData();
    void updateProjections();
    void updateAxesRange();
    void updateAxesTitle();
    void clearProjections();
    void clearProjection(SessionItem* item);
    void onIntensityItemPropertyChanged(const QString& propertyName);
    void onAxisPropertyChanged(const QString& axisName, const QString& propertyName);

    void setGraphFromItem(QCPGraph* graph, SessionItem* item);

    void setInterpolate(bool isInterpolated);
    void setLogz(bool isLogz);

    void replot();

    bool isHorizontalType();

    QString m_projectionType;
    QCustomPlot* m_customPlot;
    std::unique_ptr<Histogram2D> m_hist2d;
    QMap<SessionItem*, QCPGraph*> m_item_to_graph;
    bool m_block_plot_update;
};

#endif // PROJECTIONSPLOT_H
