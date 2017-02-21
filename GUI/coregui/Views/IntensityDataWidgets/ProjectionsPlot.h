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
#include <memory>
#include <QMap>

class QCustomPlot;
class IntensityDataItem;
class Histogram2D;
class QCPGraph;

//! A customplot based widget to display projections of IntensityDataItem on X,Y axes.

class BA_CORE_API_ ProjectionsPlot : public SessionItemWidget
{
    Q_OBJECT

public:
    ProjectionsPlot(QWidget* parent = 0);
    virtual ~ProjectionsPlot();

    void setItem(SessionItem* projectionContainerItem);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

    void onChildPropertyChanged(SessionItem* item, const QString& property);

private:
    IntensityDataItem* intensityItem();
    QCPGraph* addGraphForItem(SessionItem*item);

    QCustomPlot* m_customPlot;
    std::unique_ptr<Histogram2D> m_hist2d;
    QMap<SessionItem*, QCPGraph*> m_item_to_graph;
    bool m_block_plot_update;
};

#endif // PROJECTIONSPLOT_H
